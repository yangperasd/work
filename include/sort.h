/*************************************************************************
	> File Name: include/sort.h
	> Author: yang 
	> Mail: yangperasd@163.com 
	> Created Time: Sun 26 Mar 2017 04:52:17 PM CST
 ************************************************************************/

#ifndef _INCLUDE_SORT_H
#define _INCLUDE_SORT_H 
#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>
using std::distance;using std::cout;using std::endl;using std::iter_swap;using std::iterator_traits;using std::swap;using std::vector;
template<typename Container>
void print(Container const& c)
{/*{{{*/
    for(auto& elem:c)
    {
        std::cout<<elem<<"\t";
    }
    std::cout<<std::endl;
}/*}}}*/
template<typename It>
void print(It beg,It end)
{/*{{{*/
    for(;beg!=end;++beg)
    {
        std::cout<<*beg<<"\t";
    }
    std::cout<<std::endl;
}/*}}}*/

//insert sort 
template <typename It>
void insertSort(It beg,It end)
{/*{{{*/
    using value_type=typename It::value_type;
    for(It cur=beg+1;cur!=end;++cur)
    {
        if(*(cur-1)>*cur)
        {
            value_type tmp=*cur;
            It cpCur=cur-1;
            for(;cpCur>=beg&&*cpCur>tmp;--cpCur)
                *(cpCur+1)=*cpCur;
            *(cpCur+1)=tmp;
        }
    }
}/*}}}*/

//shell sort 
template <typename It>
void shellSort(It beg,It end)
{/*{{{*/
    size_t dk=distance(beg,end);
    while(dk/=2)
    {
        for(It cur=beg+dk;cur!=end;++cur)
        {
            if(*(cur-dk)>*cur)
            {
                typename It::value_type tmp=*cur;
                It cpCur=cur-dk;
                for(;cpCur>=beg&&*cpCur>tmp;cpCur-=dk)
                    *(cpCur+dk)=*cpCur;
                *(cpCur+dk)=tmp;
            }
        }
    }
}/*}}}*/

//select sort 
template <typename It>
void selectSort(It beg,It end)
{/*{{{*/
    for(;beg!=end;++beg)
    {
        //find min 
        It it=beg+1;
        It minIt=beg;
        for(;it!=end;++it)
            if(*it<*minIt)  minIt=it;
        if(minIt!=beg)
        {
            //NOTE: swap just shallow swap, not deep swap,
            //NOTE: iter_swap is deep swap;
            std::swap(*beg,*minIt);
        }
    }
}/*}}}*/

//select sort improvement
template <typename It>
void selectSort2(It beg,It end)
{/*{{{*/
    size_t len=distance(beg,end);
    for(int i=0;i<len/2;++i,++beg,--end)
    {
        It maxIt=beg;
        It minIt=beg;
        It it=beg+1;
        for(;it!=end;++it)
        {
            if(*maxIt<*it)
                maxIt=it;
            else if(*minIt>*it)
                minIt=it;
        }
        if(beg!=minIt)
            iter_swap(beg,minIt);
        if(maxIt!=end-1)
            iter_swap(maxIt,end-1);
    }
}/*}}}*/

//heap adjust for heap sort 
template <typename It,typename Diff>
void heapAdjust(It beg,Diff holeIndex,Diff len)
{/*{{{*/
    using value_type=typename iterator_traits<It>::value_type;
    if(len<2)
        return;
    //the element need to be adjusted 
    value_type value(*(beg+holeIndex));

    //HERE: child is not an Iterator, just an offset 
    Diff child=2*holeIndex+1;
    while(child<len)
    {
        //find max elem between left child and right child 
        if((child+1)<len&&*(beg+child+1)>*(beg+child))
            ++child;
        if(value<*(beg+child))
        {
            *(beg+holeIndex)=*(beg+child);
            holeIndex=child;
            child=2*holeIndex+1;
        }
        else
            break;
    }
    //the lastest parent is the position of value
    *(beg+holeIndex)=value;
}/*}}}*/

//build a heap for heap sort  
template <typename It,typename Diff>
void heapBuild(It beg,Diff len)
{/*{{{*/
    if(len<2)
        return;
    Diff parent=(len-2)/2;
    while(true)
    {
        heapAdjust(beg,parent,len);
        //when parent ==0 ,we should also do heapAdjust
        if(parent==0)
            break;
        --parent;
    }
}/*}}}*/

//heap sort 
template <typename It>
void heapSort(It beg,It end)
{/*{{{*/
    using Diff=typename iterator_traits<It>::difference_type;
    Diff len=distance(beg,end);
    //build heap 
    heapBuild(beg,len);
    //we should do n-1 swap
    for(Diff i=1;i<len;++i)
    {
        //swap beg with the current last one 
        iter_swap(beg,beg+len-i);
        heapAdjust(beg,Diff{0},len-i);
    }
}/*}}}*/

//bubble sort 
template <typename It>
void bubbleSort(It beg,It end)
{/*{{{*/
    if(beg==end)
        return;
    It origin{beg};
    bool flag=false;
    for(;beg<end-1;--end)
    {
        for(It cur=beg;cur<end-1;++cur)
        {
            if(*(cur+1)<*cur)
            {
                iter_swap(cur,cur+1);
                flag=true;
            }
        }
        if(!flag)
            break;
    }
}/*}}}*/

//bubble sort improvement 
template <typename It>
void bubbleSort1(It beg,It end)
{/*{{{*/
    if(beg==end)
        return;

    using Diff=typename iterator_traits<It>::difference_type;
    //first is the first time to swap, last is the last time to swap;
    It first=beg,last=end-1;
    for(;first!=last;)
    {/*{{{*/
        It cur=first;
        bool flag=false;
        end=last;
        for(;cur<end;++cur)
        {/*{{{*/
            if(*cur>*(cur+1))
            {
                last=cur;
                iter_swap(cur,cur+1);
                flag=true;
            }
            if(!flag)
            {
                if(cur!=beg)
                    first=cur-1;
            }
        }/*}}}*/
        //last bubble sort no swap, so the sequence is ordered
        if(!flag)
            break;
    }/*}}}*/

}/*}}}*/

//bubble sort improvement 
//twice bubble 
template <typename It>
void bubbleSort2(It beg,It end)
{/*{{{*/
    if(beg==end)
        return ;
    --end;
    while(beg<end)
    {/*{{{*/
        //forward bubble 
        for(It cur=beg;cur!=end;++cur)
        {
            if(*cur>*(cur+1))
                iter_swap(cur,cur+1);
        }
        --end;
        //backward bubble
        for(It cur=end;cur!=beg;--cur)
        {
            if(*cur<*(cur-1))
                iter_swap(cur,cur-1);
        }
        ++beg;
    }/*}}}*/
}/*}}}*/

//partition for quick sort 
template <typename It>
It partition(It beg,It end)
{/*{{{*/
    if(beg==end||(beg+1)==end)
        return beg;
    using value_type=typename iterator_traits<It>::value_type;
    using Diff=typename iterator_traits<It>::difference_type;
    iter_swap(beg,--end);
    //small and it's previous element are small than axie 
    Diff small{-1};
    It start(beg);
    for(;beg!=end;++beg)
    {
        if(*beg<*end)
        {
            ++small;
            if((start+small)!=beg)
            {
                iter_swap(start+small,beg);
            }
        }
    }
    It axie=start+small+1;
    iter_swap(end,axie);
    return axie;
}/*}}}*/

//quick sort 
template <typename It>
void quickSort(It beg,It end)
{/*{{{*/
    if(beg==end||(beg+1)==end)
        return;
    It axie=partition(beg,end);
    if(axie!=beg)
        quickSort(beg,axie);
    if(axie+1!=end)
        quickSort(axie+1,end);
}/*}}}*/

//merge for merge sort 
//destination must guarantee the space is enough for [first1,end1) and [first2,end2)
template <typename It>
void merge(It first1,It end1,
            It first2,It end2,
            It dstBeg)
{/*{{{*/
    It tmp=dstBeg;
    while(first1!=end1&&first2!=end2)
    {
        if(*first1<*first2)
            *dstBeg++=*first1++;
        else
            *dstBeg++=*first2++;
    }
    while(first1!=end1)
        *dstBeg++=*first1++;
    while(first2!=end2)
        *dstBeg++=*first2++;
}/*}}}*/

//merge sort 
//iteration version 
template <typename It>
void mergeSort(It beg,It end)
{/*{{{*/
    using Diff=typename iterator_traits<It>::difference_type;
    using value_type=typename iterator_traits<It>::value_type;
    Diff Length=distance(beg,end);
    vector<value_type> tmp(Length); 
    for(size_t len=1;len<Length;len*=2)
    {/*{{{*/
        //merge to list with same length 
        size_t i=0;
        for(;i+2*len<=Length;i+=2*len)
        {
            merge(beg+i,beg+i+len,
                  beg+i+len,beg+i+2*len,
                  tmp.begin()+i); 
        }
        //merge surplus list 
        if(i+len<Length)
            merge(beg+i,beg+i+len,
                  beg+i+len,beg+Length-1,
                  tmp.begin()+i);
        //overwrite source with tmp 
        std::copy(tmp.begin(),tmp.end(),
                 beg);
        //print(beg,end);
    }/*}}}*/
}/*}}}*/

//radix sort

#endif
