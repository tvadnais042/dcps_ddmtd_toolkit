#include "orm.h"

int ORM_get_constant0(void)
{ return(spi_get_16bits(ORM_CONSTANT0)); }


int ORM_put_constant0(int value16bits)
{return(spi_put_16bits(ORM_CONSTANT0,value16bits));}


int ORM_get_constant1(void)
{ return(spi_get_16bits(ORM_CONSTANT1)); }

int ORM_get_dummy0(void)
{ return(spi_get_16bits(ORM_DUMMY_REG0)); }

int ORM_put_dummy0(int value16bits)
{ return(spi_put_16bits(ORM_DUMMY_REG0, value16bits)); }

int ORM_get_dummy1(void)
{ return(spi_get_16bits(ORM_DUMMY_REG1)); }

int ORM_put_dummy1(int value16bits)
{ return(spi_put_16bits(ORM_DUMMY_REG1, value16bits)); }
