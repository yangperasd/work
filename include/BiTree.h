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
#include <iterator>
#include <algorithm>
#include <stdexcept>
using std::endl;using std::cout;using std::stack;using std::pair;using std::tie;using std::queue;using std::find;using std::distance;using std::runtime_error;
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
    using pointer=BiTreeNode<T> *;
    using Base=BiTreeNodeBase;
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
    void freeNode(Base* p)
    {
        if(p)
        {
            if(p->m_pLeft)
                freeNode(p->m_pLeft);
            if(p->m_pRight)
                freeNode(p->m_pRight);
            delete static_cast<pointer>(p);
        }
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
        ~BiTree()
        { 
             m_root->freeNode(m_root);
        }
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
                traverseRecursionImpl(static_cast<iterator>(pNode->m_pLeft)
                                        ,mode);
                if(mode==1)
                    pNode->visit();
                traverseRecursionImpl(static_cast<iterator>(pNode->m_pRight),
                                        mode);
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
template<typename T,typename Iterator>
BiTreeNode<T>* 
reBuildFromMidFirstOrderImpl(Iterator preOrderBeg,Iterator preOrderEnd,
                                  Iterator midOrderBeg,Iterator midOrderEnd)
{
    if(preOrderBeg==preOrderEnd||midOrderBeg==midOrderEnd)
    {
        return nullptr;
    }
    using Node_t=BiTreeNode<T>;
    //find root in mid-order 
    auto pos=find(midOrderBeg,midOrderEnd,*preOrderBeg);
    //do not find root in mid-order,ERROR!
    if(pos==midOrderEnd)
    {
        throw runtime_error("do not find root in mid-order");
        return nullptr;

    }
    //build root 
    Node_t* root=new Node_t(*preOrderBeg);
    size_t leftLen=distance(midOrderBeg,pos);
    //build left child 
    if(pos!=midOrderBeg)
    {
        root->m_pLeft=reBuildFromMidFirstOrderImpl<T>(preOrderBeg+1,preOrderBeg+leftLen+1,
                                                  midOrderBeg,pos);
    }
    //build right child
    if(pos!=midOrderEnd)
    {
        root->m_pRight=reBuildFromMidFirstOrderImpl<T>(preOrderBeg+leftLen+1,preOrderEnd,
                                                   pos+1,midOrderEnd);
    }
    return root;
}
template<typename T,typename Container>
void reBuildFromMidFirstOrder(BiTree<T>& tree,Container const& preOrder,
                             Container const& midOrder)
{
    if(!tree.m_root)
        tree.m_root=reBuildFromMidFirstOrderImpl<T>(preOrder.begin(),preOrder.end(),
                                                midOrder.begin(),midOrder.end());
}
#endif
