// Author:陳柏翰
// Date:Oct 23,2020
// Purpose:Calculate addition and multiplication of polynominal
using namespace std;

struct node{
    int co,ex;                                                      //struct node contains int 'co'(coefficient),'ex'(exponent)
    node *next;                                                     //and pointer 'next'(point to next node)
    node(int c,int e){co=c; ex=e; next=NULL;}                       //constructor for node(set co,ex,and set 'next' to NULL)
};

class Poly{
    private:
        node *top;                                                  //private var 'top'(point to the highest co of polynominal)
    public:
        Poly(){top=NULL;}                                           //constuctor of Poly(set top to NULL)
        void add(int,int);
        void remove();
        void print();
        friend Poly operator + (const Poly &p1,const Poly &p2);
        friend Poly operator * (const Poly &p1,const Poly &p2);
};

void Poly::add(int c,int e){                                        //add new node into the polynominal
    node *new_node=new node(c,e);                                   //node pointer'new_node' get the new coefficient、exponent
    if(top==NULL){
        top=new_node;                                               //if no node in Poly,'top' point to new_node
        return;
    }
    else if(top->next==NULL){                                       // if there is only one node in Poly
        if(top->ex<new_node->ex){   
            new_node->next=top;                                     // and ex of node larger than ex of top,let new_node be the top of Poly
            top=new_node;
        }
        else if(top->ex==new_node->ex) top->co+=new_node->co;       // and ex of node equal to ex of top,add the co of new_node to top
        else{
            top->next=new_node;                                     // and ex of node smaller than ex of top,new_node will be the next of top
        }
    }
    else{
        node *current=top;                                          // set node pointer 'current' be 'top'
        while(current->next!=NULL){
            if(current==top && current->ex<new_node->ex){           // if ex of node larger than ex of top,let new_node be the top of Poly
                new_node->next=current;
                top=new_node;
                return;
            }
            else if(current->ex==new_node->ex){                     // ex of node equal to ex of top,add the co of new_node to 'current'
                current->co+=new_node->co;
                return;
            }
            else if(current->ex>new_node->ex && current->next->ex<new_node->ex){    // get the current that ex of new_node"lesser than ex of current" and "larger than ex of current->next"
                if(current==top){                                   // current is 'top',set current->next be new_node->next,and let new_node be 'top'
                    new_node->next=current->next;
                    top->next=new_node;
                    return;
                }
                else{
                    new_node->next=current->next;                   // other condition: put new_node between current and current->next
                    current->next=new_node->next;
                    current->next=new_node;
                    return;
                }
            }
            current=current->next;
        }
        if(current->ex==new_node->ex) current->co+=new_node->co;    // ex of last node equal to ex of new_node,add it
        else current->next=new_node;                                // otherwise put new_node behind the last node
    }
}

void Poly::remove(){
    node *current=top,*del_node;                                    // node pointer 'current'(set to 'top'),del_node(the node has to delete)
    while(current->next){
        if(current->co==0 && current==top){                         // if co of current is 0 and current is 'top',set 'top' to current->next,than delete
            del_node=current;
            top=del_node->next;
            delete del_node;
        }
        else if(current->next->co==0){                              // if co of current->next is 0, set current->next to current->next->next,then delete
            del_node=current->next;
            current->next=current->next->next;
            delete del_node;
        }
        if(current->next) current=current->next;                    // if current is not the last node,let current be current->next
    }
}

void Poly::print(){
    node *current=top;                                              // node pointer 'current'(set to 'top')
    while(current!=NULL){
        cout << current->co << " " << current->ex << endl;          // print 'co' and 'ex' of current
        current=current->next;
    }
}

Poly operator +(const Poly &p1,const Poly &p2){
    Poly p3;                                                        // set new Poly p3 be the result of addition
    node *p1_curr=p1.top,*p2_curr=p2.top;                           // node pointer p1_curr(set to p1.top),p2_curr(set to p2.top)
    while(p1_curr){
        p3.add(p1_curr->co,p1_curr->ex);                            // add node of p1 to p3
        p1_curr=p1_curr->next;
    }
    while(p2_curr){
        p3.add(p2_curr->co,p2_curr->ex);                            // add node of p2 to p3
        p2_curr=p2_curr->next;
    }
    p3.remove();                                                    // remove the zero-co node of p3
    return p3;
}

Poly operator *(const Poly &p1,const Poly &p2){
    Poly p3;                                                        // set new Poly p3 be the result of multiplication
    node *p1_curr=p1.top,*p2_curr=p2.top;                           // node pointer p1_curr(set to p1.top),p2_curr(set to p2.top)
    if(!p1_curr || !p2_curr){                                       // if p1==0 and p2==0 ,p3=0
        p3.add(0,0);
        return p3;
    }
    while(p1_curr){
        p2_curr=p2.top;
        while(p2_curr){
            p3.add(p1_curr->co*p2_curr->co,p1_curr->ex+p2_curr->ex);        // add p1 and p2 s' node-by-node mulplication to p3
            p2_curr=p2_curr->next;
        }
        p1_curr=p1_curr->next;
    }
    p3.remove();                                                    // remove the zero-co node of p3
    return p3;
}