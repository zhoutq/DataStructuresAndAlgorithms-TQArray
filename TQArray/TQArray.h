//
//  TQArray.h
//  TQArray
//
//  Created by ztq on 2017/11/25.
//  Copyright © 2017年 ztq. All rights reserved.
//

#ifndef TQArray_h
#define TQArray_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef void * tq;
typedef void (*DataDestroy)(tq); // 销毁函数
typedef bool (*DataCmp)(tq, tq); // 比较函数 (暂时未用)
typedef void (*DataPrintf)(tq);  // 打印函数

typedef struct ArrayItem {
    
    tq *m_ppData; // 数组数据存储地址
    int m_nAllocSize; // 分配空间大小
    int m_nSize; // 实际占用大小
//    DataDestroy m_fDestroy; // 数据销毁函数
//    DataCmp m_fCmp; // 数据比较函数
//    DataPrintf m_fPrintf; // 数据打印函数
}TQArrayItem, *TQArray;

/**
 动态数组：根据添加元素，自动增减大小
 */

/**
 创建数据，分配空间

 @param nAllocSize 分配空间大小
 @return 分配空间大小的数据地址
 */
TQArray TQArrayCreate(int nAllocSize);

/**
 在指定索引插入数据

 @param pArray 被插入数组地址
 @param nIndex 索引
 @param tqData 待插入数据
 @return 结果反馈， true 成功， false 失败
 */
bool TQArrayInsertAtIndex(TQArray pArray, int nIndex, tq tqData);

/**
 数组追加数据

 @param pArray 被追加数组地址
 @param tqData 待追加数据
 @return 结果反馈， true 成功， false 失败
 */
bool TQArrayAppend(TQArray pArray, tq tqData);

/**
 获取指定索引的数据

 @param pArray 被索引数组地址
 @param nIndex 索引
 @param tqData 索引输出数据
 @return 结果反馈， true 成功， false 失败
 */
bool TQArrayGetByIndex(TQArray pArray, int nIndex, tq *tqData);

/**
 获取最后一个数据

 @param pArray 数组地址
 @param tqData 输出数据
 @return 结果反馈， true 成功， false 失败
 */
bool TQArrayGetLast(TQArray pArray, tq *tqData);

/**
 删除指定索引数据

 @param pArray 数组地址
 @param nIndex 索引
 @param pDataDestroy 数据销毁函数
 @return 结果反馈， true 成功， false 失败
 */
bool TQArrayDelete(TQArray pArray, int nIndex, DataDestroy pDataDestroy);

/**
 获取数组长度
 
 @param pArray 数组地址
 @return 数组长度， 大于等于0 成功， -1 失败
 */
int TQArrayLength(TQArray pArray);

/**
 打印数组数据

 @param pArray 被打印数组地址
 @param pDataPrintf 数据打印函数
 @return 结果反馈， true 成功， false 失败
 */
bool TQArrayPrintf(TQArray pArray, DataPrintf pDataPrintf);

/**
 销毁数组
 
 @param pArray 数组地址
 @param pDataDestroy 数据销毁函数
 */
void TQArrayDestroy(TQArray pArray, DataDestroy pDataDestroy);

#endif /* TQArray_h */
