#ifndef __MUSIC_RHYTHM_H__
#define __MUSIC_RHYTHM_H__

/* 有源蜂鸣器(2.7kHz固定音高)只能开关，用节奏模拟"哈哈哈"
   格式: {响ms, 停ms, ...}
   每组 = 3 连击(ha-ha-ha) + 换气停顿 */

#define RHYTHM_N 13

const unsigned short rhythm_tab[26]={
    70,50,  65,45,  90,330,      /* 哈哈哈 */
    75,50,  65,45,  95,300,      /* 哈哈哈 */
    70,50,  70,45, 100,340,      /* 哈哈哈 */
    80,50,  70,45, 110,300,      /* 哈哈哈 */
    260,400                      /* 最后一声长"哈——" 换气 */
};

#endif
