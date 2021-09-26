/* adlist.h - A generic doubly linked list implementation
 *
 * Copyright (c) 2006-2012, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __ADLIST_H__
#define __ADLIST_H__

/* Node, List, and Iterator are the only data structures used currently. */

typedef struct listNode {
    // 前置节点
    struct listNode *prev;
    // 后置节点
    struct listNode *next;
    // 节点的值
    void *value;
} listNode;

typedef struct listIter {
    listNode *next;
    int direction;
} listIter;

typedef struct list {
    // 表头节点
    listNode *head;
    // 表尾节点
    listNode *tail;
    // 节点值复制函数，用于复制链表节点所保存的值
    void *(*dup)(void *ptr);
    // 节点值释放函数,用于释放链表节点所保存的值
    void (*free)(void *ptr);
    // 节点值对比函数，用于比较链表节点所保存的值和另一个值是否相等
    int (*match)(void *ptr, void *key);
    // 链表所包含的节点数量
    unsigned long len;
} list;

/* Functions implemented as macros */
// 返回链表的长度，时间复杂度O(1)
#define listLength(l) ((l)->len)
// 返回链表的头节点，时间复杂度O(1)
#define listFirst(l) ((l)->head)
// 返回链表的尾部节点，时间复杂度O(1)
#define listLast(l) ((l)->tail)
// 返回给定节点的前置节点，时间复杂度O(1)
#define listPrevNode(n) ((n)->prev)
// 返回给定节点的后置节点，时间复杂度O(1)
#define listNextNode(n) ((n)->next)
// 返回给定节点保存的值，时间复杂度O(1)
#define listNodeValue(n) ((n)->value)
// 将给定函数设置为链表的节点值复制函数
#define listSetDupMethod(l,m) ((l)->dup = (m))
// 将给定函数设置为链表的节点值释放函数
#define listSetFreeMethod(l,m) ((l)->free = (m))
// 将给定函数设置为链表的节点值对比函数
#define listSetMatchMethod(l,m) ((l)->match = (m))
// 返回当前正在使用的节点值复制函数
#define listGetDupMethod(l) ((l)->dup)
// 返回链表当前正在使用的节点值释放函数
#define listGetFree(l) ((l)->free)
// 返回链表当前正在使用的节点值对比函数
#define listGetMatchMethod(l) ((l)->match)

/* Prototypes */
// 创建一个不包含任何节点的新链表
list *listCreate(void);
// 释放给定链表，以及链表中所有节点
void listRelease(list *list);
// 将一个新元素添加到链表表头
list *listAddNodeHead(list *list, void *value);
// 将一个新元素添加到链表表尾
list *listAddNodeTail(list *list, void *value);
// 将一个新元素添加到链表指定元素之前或者之后，after=1，为之后
list *listInsertNode(list *list, listNode *old_node, void *value, int after);
// 从链表删除指定节点
void listDelNode(list *list, listNode *node);
// 创建链表迭代器
listIter *listGetIterator(list *list, int direction);
// 获取当前迭代节点
listNode *listNext(listIter *iter);
// 释放迭代器
void listReleaseIterator(listIter *iter);
// 复制链表
list *listDup(list *orig);
// 查找链表包含指定值得节点
listNode *listSearchKey(list *list, void *key);
// 返回链表指定位置上的节点
listNode *listIndex(list *list, long index);
// 重置迭代器到表头节点
void listRewind(list *list, listIter *li);
// 重置迭代器到表尾节点
void listRewindTail(list *list, listIter *li);
// 链表尾部节点移动到链表头部节点
void listRotate(list *list);

/* Directions for iterators */
#define AL_START_HEAD 0
#define AL_START_TAIL 1

#endif /* __ADLIST_H__ */
