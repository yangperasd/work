/*************************************************************************
	> File Name: include/BiTree.h
	> Author: yang 
	> Mail: yangperasd@163.com 
	> Created Time: Tue 07 Mar 2017 09:18:10 PM CST
 ************************************************************************/

#ifndef _INCLUDE_BITREE_H
#define _INCLUDE_BITREE_H 
#include <iostream>
#include <stack>
#include <utility>
#include <tuple>
#include <queue>
using std::endl;using std::cout;using std::stack;using std::pair;using std::tie;using std::queue;
struct BiTreeNodeBase
{/*{{{*/
    //ctor 
    BiTreeNodeBase():m_pLeft(nullptr),m_pRight(nullptr) {}
    //data member 
    BiTreeNodeBase* m_pLeft;
    BiTreeNodeBase* m_pRight;
};/*}}}*/

template <typename T>
struct BiTreeNode: public BiTreeNodeBase
{
    //some type rename 
    using pointer=BiTreeNode*;
    using selfType=BiTreeNode<T>;
    //ctor 
    BiTreeNode(T const& value):m_data(value),BiTreeNodeBase() {}
    //data member 
    T m_data;
    //utility 
    pointer insertLeft(T const& value) 
    {/*{{{*/
        pointer* pNewNode=new selfType(value);
        if (!pNewNode)
            return nullptr;
        this->m_pLeft=pNewNode;
        return pNewNode;
    }/*}}}*/

    pointer insertRight(T const& value) 
    {/*{{{*/
        pointer* pNewNode=new selfType(value);
        if (!pNewNode)
            return nullptr;
        this->m_pRight=pNewNode;
        return pNewNode;
    }/*}}}*/
    pointer deleteLeft()
    {
        return this;
    }
    
    void visit()
    {
        cout<<this->m_data<<endl;
    }
};


template <typename T=int>
class BiTree 
{
    public:
        //some rename 
        using Node_t=BiTreeNode<T>;
        using iterator=Node_t *;
    public:
        BiTree():m_root(nullptr),m_len(0) {};
        
        void traverse(int mode=0)
        { /*{{{*/
            //0 for pre-order,1 for mid-order,2 for post-order 
            if(mode<0&&mode>2)
            {
                cout<<"traverse mode error,you specify:"<<mode<<endl;
                return ;
            }
            return traverseRecursionImpl(m_root,mode);
        }/*}}}*/
        
        void traverseLoopVersion(int mode=0)
        { /*{{{*/
            //0 for pre-order,1 for mid-order,2 for post-order, 3 for level-order
            if(mode<0&&mode>3)
            {
                cout<<"traverse mode error,you specify:"<<mode<<endl;
                return ;
            }
            
            iterator cur=m_root;
            
            //level-order 
            if(mode==3)
            {/*{{{*/
                //empty tree
                if(!cur)
                    return;
                queue<iterator> q;
                q.push(cur);
                
                //start traverse
                while(!q.empty())
                {
                    iterator iter=q.top();
                    q.pop();
                    iter->visit();
                    if(iter->m_pLeft)
                        q.push(iter->m_pLeft);
                    if(iter->m_pRight)
                        q.push(iter->m_pRight);
                }
            }/*}}}*/
            //pre-order, mid-order, post-order
            else
            { /*{{{*/
                stack<pair<iterator,bool>> s; //fist elem for pointer, second elem for visit count

                //start traverse 
                while(!s.empty()||cur)
                {/*{{{*/
                    while(cur)
                    {
                        if(mode==0)
                            //pre-order
                            cur->visit();
                        s.push({cur,0});
                        cur=cur->m_pLeft;
                    }
                    if(!s.top()->second)
                    {/*{{{*/
                        //post-order 
                        //second visit this node, so to visit this node's right child
                        if(mode==2)
                        {
                            s.top()->second=true;
                            cur=s.top()->first->m_pRight;
                        }
                        //pre-order and mid-order
                        else
                        {
                            tie(cur,std::ignore)=s.top();
                            //mid-order
                            if(mode==1)
                                cur->visit();
                            s.pop();
                            cur=cur->m_pRight;
                        }
                    }/*}}}*/
                    else
                    {/*{{{*/
                        //post-order 
                        //we have visit this node twice, so pop and visit it 
                        while(s.top()->second)
                        {
                            s.top()->visit();
                            s.pop();
                        }
                        //directly to visit it's right child
                        cur=nullptr;
                    }/*}}}*/
                }/*}}}*/
                
            }/*}}}*/

        }/*}}}*/
        
        iterator insertLeft(iterator pNode,T const& value) 
        {/*{{{*/
            if(pNode)
            {
                return pNode->insertLeft(value);
            }
            else 
                return nullptr;
        }/*}}}*/

        iterator insertRight(iterator pNode,T const& value) 
        {/*{{{*/
            if(pNode)
            {
                return pNode->insertRight(value);
            }
            else 
                return nullptr;
        }/*}}}*/
    protected:
        void traverseRecursionImpl(iterator pNode,int mode=0)
        { /*{{{*/
            if(pNode)
            {
                if(mode==0)
                    pNode->visit();
                traverseRecursionImpl(pNode->m_pLeft,mode);
                if(mode==1)
                    pNode->visit();
                traverseRecursionImpl(pNode->m_pRight,mode);
                if(mode==2)
                    pNode->visit();
                return;
            }
        }/*}}}*/
        
    public:
        //data member
        Node_t*     m_root;
        size_t      m_len;
};
#endif
