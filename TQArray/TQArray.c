//
//  TQArray.c
//  TQArray
//
//  Created by ztq on 2017/11/25.
//  Copyright © 2017年 ztq. All rights reserved.
//

#include "TQArray.h"

/**
 对数组进行扩展
 
 @param pArray 被扩展数组地址
 @param nIncrement 扩展增量
 @return 结果反馈， true 成功， false 失败
 */
bool TQArrayExpand(TQArray pArray, int nIncrement);

/**
 对数组进行缩减
 
 @param pArray 被缩减数组地址
 @return 结果反馈， true 成功， false 失败
 */
bool TQArrayShrink(TQArray pArray);

TQArray TQArrayCreate(int nAllocSize)
{
    TQArray pArray = NULL;
    pArray = (TQArray)malloc(sizeof(TQArrayItem)); // 为数组开辟空间
    if (!pArray) {
        
        return NULL;
    }
    
    memset(pArray, 0, sizeof(TQArrayItem));
    
    pArray->m_ppData = (tq)malloc(nAllocSize * sizeof(tq)); // 为数据存储开辟 nAllocSize 大小的空间
    if (!pArray->m_ppData) {
        
        free(pArray);
        return NULL;
    }
    
    pArray->m_nAllocSize = nAllocSize;
    
    return pArray;
}

bool TQArrayInsertAtIndex(TQArray pArray, int nIndex, tq tqData)
{
    int nCursor = nIndex;
    
    if (!pArray || nIndex < 0) {
        
        return false;
    }
    
    nCursor = nCursor < pArray->m_nSize ? nCursor: pArray->m_nSize; // 保证数据连续
    
    if (TQArrayExpand(pArray, 1)) {
        
        // 将待插入及其后面的数据后移
        for ( int i = pArray->m_nSize; i> nCursor; i--) {
            
            pArray->m_ppData[i] = pArray->m_ppData[i - 1];
        }
        
        pArray->m_ppData[nCursor] = tqData; // 插入数据
        pArray->m_nSize++; // 数据占用空间大小自增
    }
    
    return true;
}

bool TQArrayAppend(TQArray pArray, tq tqData)
{
    return TQArrayInsertAtIndex(pArray, pArray->m_nSize, tqData);
}

bool TQArrayGetByIndex(TQArray pArray, int nIndex, tq *tqData)
{
    if (!pArray || nIndex < 0 || nIndex >= pArray->m_nSize || !tqData) {
        
        return false;
    }
    
    *tqData = pArray->m_ppData[nIndex];
    
    return true;
}

bool TQArrayGetLast(TQArray pArray, tq *tqData)
{
    return TQArrayGetByIndex(pArray, pArray->m_nSize, tqData);
}

bool TQArrayDelete(TQArray pArray, int nIndex, DataDestroy pDataDestroy)
{
    if (!pArray || nIndex < 0 || nIndex >= pArray->m_nSize) {
        return false;
    }
    
    // 利用销毁函数，销毁数组数据
    if (pDataDestroy) {
        
        pDataDestroy(pArray->m_ppData[nIndex]);
    }
    
    // 数据前移
    for (int i = nIndex; i < pArray->m_nSize; i++) {
        
        pArray->m_ppData[i] = pArray->m_ppData[i + 1];
    }
    
    pArray->m_ppData[pArray->m_nSize] = NULL;
    pArray->m_nSize--;
    
    TQArrayShrink(pArray); // 缩减空间
    return true;
}

int TQArrayLength(TQArray pArray)
{
    return pArray ? pArray->m_nSize : -1;
}

bool TQArrayPrintf(TQArray pArray, DataPrintf pDataPrintf)
{
    if (!pArray || !pDataPrintf) {
        
        return false;
    }
    
    for (int i = 0; i < pArray->m_nSize; i++) {
        
        pDataPrintf(pArray->m_ppData[i]);
    }
    
    return true;
}

void TQArrayDestroy(TQArray pArray, DataDestroy pDataDestroy)
{
    if (!pArray) {
        return;
    }
    
    if (pDataDestroy) {
        
        for (int i = 0; i < pArray->m_nSize; i++) {
            
            pDataDestroy(pArray->m_ppData[i]);
        }
    }
    
    free(pArray->m_ppData);
    pArray->m_ppData = NULL;
    free(pArray);
    pArray = NULL;
}

bool TQArrayExpand(TQArray pArray, int nIncrement)
{
    int nNewAllocSize = 0;
    tq *pNewData = NULL;
    
    if (!pArray) {
        
        return false;
    }
    
    if ( pArray->m_nAllocSize < (pArray->m_nSize + nIncrement)) {
        
        nNewAllocSize = pArray->m_nAllocSize + (pArray->m_nAllocSize >> 1); // 开辟原来1.5倍大小的空间
        pNewData = (tq *)realloc(pArray->m_ppData, nNewAllocSize * sizeof(tq));
        if (pNewData) {
            memset(pNewData + pArray->m_nAllocSize, 0, (nNewAllocSize - pArray->m_nAllocSize) * sizeof(tq)); // 新开辟空间初始化
            pArray->m_ppData = pNewData;
            pArray->m_nAllocSize = nNewAllocSize;
        }
    }
    
    return (pArray->m_nAllocSize >= (pArray->m_nSize + nIncrement)) ? true : false;
    
}

bool TQArrayShrink(TQArray pArray)
{
    int nNewAllocSize = 0;
    tq *pNewData = NULL;
    
    if (!pArray) {
        
        return false;
    }
    
    if (pArray->m_nSize < (pArray->m_nAllocSize >> 1) ) { // 实际使用空间 小于 开辟空间的二分之一
        
        nNewAllocSize = pArray->m_nSize + (pArray->m_nSize >> 1); // 将空间开辟为使用空间1.5倍大小
        pNewData = (tq *)realloc(pArray->m_ppData, nNewAllocSize * sizeof(tq));
        if (pNewData) {
            memset(pNewData + pArray->m_nSize, 0, (nNewAllocSize - pArray->m_nSize) * sizeof(tq)); // 新开辟空间初始化
            pArray->m_ppData = pNewData;
            pArray->m_nAllocSize = nNewAllocSize;
        }
    }
    
    return true;
}
