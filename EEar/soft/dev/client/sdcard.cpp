
#include "include.h"
#include "stm324xg_eval_sdio_sd.h"



bool CSDCard::b_init_ok = false;



bool CSDCard::InitCard()
{
  b_init_ok = (SD_Init() == SD_OK && SD_Detect() == SD_PRESENT);
  
  if ( b_init_ok )
     {
       NVIC_InitTypeDef NVIC_InitStructure;
       NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
       NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
       NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
       NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
       NVIC_Init(&NVIC_InitStructure);

       NVIC_InitStructure.NVIC_IRQChannel = SD_SDIO_DMA_IRQn;
       NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
       NVIC_Init(&NVIC_InitStructure);  
     }

  return b_init_ok;
}


unsigned long long CSDCard::GetCardCapacity()
{
  SD_CardInfo i;
  return (b_init_ok && SD_GetCardInfo(&i) == SD_OK ? i.CardCapacity : 0);
}


bool CSDCard::Read(void *buff,unsigned start_sector,unsigned num_sectors)
{
  bool rc = false;

  if ( b_init_ok )
     {
       if ( num_sectors == 0 )
          {
            rc = true;
          }
       else
          {
            if ( buff )
               {
                 if ( SD_ReadMultiBlocks((uint8_t*)buff,(uint64_t)start_sector*SECTOR_SIZE,SECTOR_SIZE,num_sectors) == SD_OK )
                    {
                      rc = (SD_WaitReadOperation() == SD_OK);
                      while ( SD_GetStatus() != SD_TRANSFER_OK ) {}
                    }
               }
          }
     }

  return rc;
}


bool CSDCard::Write(const void *buff,unsigned start_sector,unsigned num_sectors)
{
  bool rc = false;

  if ( b_init_ok )
     {
       if ( num_sectors == 0 )
          {
            rc = true;
          }
       else
          {
            if ( buff )
               {
                 if ( SD_WriteMultiBlocks((uint8_t*)buff,(uint64_t)start_sector*SECTOR_SIZE,SECTOR_SIZE,num_sectors) == SD_OK )
                    {
                      rc = (SD_WaitWriteOperation() == SD_OK);
                      while ( SD_GetStatus() != SD_TRANSFER_OK ) {}
                    }
               }
          }
     }

  return rc;
}


extern "C"
void SDIO_IRQHandler(void)
{
  SD_ProcessIRQSrc();
}


extern "C"
void SD_SDIO_DMA_IRQHANDLER(void)
{
  SD_ProcessDMAIRQ();
}


