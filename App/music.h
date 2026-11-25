#ifndef __MUSIC_H__
#define __MUSIC_H__

#include "stm32f10x.h"
#include "system.h"

/*低音部分*/
 
#define l1 523
 
#define l2 587
 
#define l3 659
 
#define l4 694
 
#define l5 784
 
#define l6 880
 
#define l7 988
 
/*中音部分*/
 
#define m1 1046
 
#define m2 1175
 
#define m3 1318
 
#define m4 1397
 
#define m5 1568
 
#define m6 1760
 
#define m7 1976
 
/*高音部分*/
 
#define h1 2092
 
#define h2 2348
 
#define h3 2636
 
#define h4 2796
 
#define h5 3139
 
#define h6 3524
 
#define h7 3956

#define p 600	//p为一段时间


#ifdef MUSIC_C
uc16 music[516]={
 
    m7,p/4,
    h1,p/4,
    h2,p/4,
    h3,p/4,
    m3,p/2,
    h5,p/4,
    h3,p/4,
	h3,p/2,
	0,p,


	m7,p/4,
    h1,p/4,
    h2,p/4,
    h3,p/4,
    m2,p/2,
    h5,p/4,
    h3,p/4,
	h2,p/4,
	h3,p/4,
	h1,p/4,
	h2,p/4,
	m7,p/4,
    h1,p/4,
    m5,p/4,
    0,p,
	0,p,
	
    m7,p/4,
    h1,p/4,
    h2,p/4,
    h3,p/4,
    m3,p/2,
    h5,p/4,
    h3,p/4,
	h3,p/2,
	0,p,

	m7,p/4,
    h1,p/4,
    h2,p/4,
    h3,p/4,
    m2,p/2,
    h5,p/4,
    h3,p/4,
	h2,p/4,
	h3,p/4,
	h1,p/4,
	h2,p/4,
	m7,p/4,
    h1,p/4,
    m5,p/4,//不和谐
    0,p,
	0,p,
	
	m2,p,
	m1,p/4,
	m2,p,
	m1,p/4,
	m2,p/2,
	m3,p/2,
	m5,p/2,
	m3,p/2,
	0,p,
	
	m2,p,
	m1,p/4,
	m2,p,
	m1,p/4,
	m2,p/4,
	m3,p/4,
	m2,p/4,
	m1,p/4,
	m1,p/2,//不和谐
	0,p,
	0,p,
	
	m2,p,
	m1,p/4,
	m2,p,
	m1,p/4,
	m2,p/2,
	m3,p/2,
	m5,p/2,
	m3,p/2,
	0,p,
	
	m2,p,
	m3,p/4,
	m2,p/2,
	m1,p/4,
	m2,p/4,
	m2,p,
	0,p,
	0,p,
	
	m2,p,
	m1,p/4,
	m2,p,
	m1,p/4,
	m2,p/2,
	m3,p/2,
	m5,p/2,
	m3,p/2,
	0,p,
	
	m2,p,
	m3,p/4,
	m2,p/2,
	m1,p/4,
	l6,p,//不和谐
	0,p,
	
	m3,p/4,
	m2,p/4,
	m1,p/4,
	m2,p/4,
	0,p,
	m1,p/2,
	0,p,
	m3,p/4,
	m2,p/4,
	m1,p/4,
	m2,p/4,
	m1,p/2,
	m3,p/4,
	m2,p/4,
	m1,p/4,
	m2,p/4,
	m1,p/2,
	
	m1,p/2,
	m2,p/2,
	m3,p/2,
	m1,p/2,
	m6,p/2,
	m5,p/4,
	m6,p/2,
	0,p,
	m1,p/4,
	m7,p/2,
	m6,p/4,
	m7,p,
	0,p,
	0,p,
	m7,p/2,
	m6,p/4,
	m7,p/2,
	m3,p/2,
	m1,p/4,//不和谐
	m2,p/4,
	m1,p/4,
	m7,p/4,
	m6,p/2,
	0,p,
	m5,p/2,
	m6,p/2,
	m5,p/4,
	m6,p/2,
	m5,p/4,
	m6,p/4,
	m5,p/4,
	m6,p/2,
	m5,p/4,
	m2,p/2,
	m5,p/4,
	0,p,
	m5,p/4,
	m3,p/2,
	m3,p/2,
	
	m1,p/2,
	m2,p/2,
	m3,p/2,
	m1,p/2,
	m6,p/2,
	m5,p/4,
	m6,p,
	0,p,
	m1,p/4,
	m7,p/2,
	m6,p/4,
	m7,p,
	0,p,
	m7,p/2,
	m6,p/4,
	m7,p,
	m3,p/2,
	h1,p/4,
	h2,p/4,
	h1,p/4,
	m7,p/4,
	m6,p/4,
	
	m5,p/2,
	m6,p/2,
	h3,p/4,
	h3,p,
	m5,p/2,
	m6,p/2,
	h3,p/4,
	h3,p/2,
	m5,p/4,
	m6,2*p,
	
	h1,p/2,
	h2,p/2,
	h3,p/2,
	h6,p/4,
	h5,p/2,
	h6,p/4,
	h5,p/2,
	h6,p/4,
	h5,p,
	h2,p/4,
	h3,p,
	h6,p/4,
	h5,p,
	h6,p/4,
	h5,p,
	h6,p/4,
	h5,p/2,
	h3,p/4,
	h3,p,
	0,p,
	
	h2,p/4,
	h2,p/4,
	h1,p/4,
	m6,p/2,
	h1,p/2,
	h1,p/4,
	h2,p/4,
	h2,p/4,
	h1,p/4,
	m6,p/4,
	
	h1,p/2,
	h3,p*1.5,
	h3,p/4,
	h2,p/4,
	h3,p/4,
	h2,p/2,
	0,p,
	
	h1,p/2,
	h2,p/2,
	h3,p/2,
	h6,p/4,
	h5,p,
	h6,p/4,
	h5,p,
	h6,p/4,
	h5,p/2,
	0,p,
	
	h2,p/4,
	h3,p/2,
	h6,p/4,
	h5,p,
	h6,p/4,
	h5,p,
	h6,p/4,
	h5,p/2,
	h3,p/2,
	0,p,
	h3,p*0.75,
	h2,p/2,
	h1,p/4,
	m6,p/2,
	h3,p/2,
	h2,p/2,
	h1,p/4,
	m6,p/2,
	m6,p/4,
	h1,p/4,
	h1,p
	
};




#else
extern uc16 music[516];
#endif

void PlayMusic(int num,uc16 music[]);




#endif
#