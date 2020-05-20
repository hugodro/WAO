#ifndef _REORDER_H_
#define _REORDER_H_
/**************************************************
* File: reorder.h.
* Desc: Implementation of byte re-ordering macros.
* Module: WAO : Librarian.
* Rev: 30 juin 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#define MakeUInt16(x)		\
		((unsigned short)((unsigned short)((x)[1]) + ((unsigned short)((x)[0]) << 8)))


#define MakeUInt32(x)		\
		((unsigned int)		\
		    (unsigned int)((x)[3]) + ((unsigned int)((x)[2]) << 8) + \
		    ((unsigned int)((x)[1]) << 16) + ((unsigned int)((x)[0]) << 24))


#define MakeUInt32Byte(x, y)	\
		(((unsigned int)(x)) << ((3 - y) * 8))

#endif		/* _REORDER_H_ */
