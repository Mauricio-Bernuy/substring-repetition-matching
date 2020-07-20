#include <vector>
#include <iostream>

using namespace std;

class Node{
public:
    int val;
    Node* izq = nullptr;
    Node* der = nullptr;
};

class Solutioner {
public:
    bool isMinHeap(Node* root){
        auto cur_val = root->val;
        int b_izq = 0; int b_der = 0;
        if (root->izq != nullptr){
            if (root->izq->val > cur_val){
                b_izq = isMinHeap(root->izq); ///counter
            }
        }
        else b_izq = 2;
        if (root->der != nullptr){
            if (root->der->val > cur_val){
                b_der = isMinHeap(root->der);
            }
        }
        else b_der = 2;
        cout<<b_der<<" "<<b_izq<<endl;
        if (b_izq >= 1 && b_der >= 1){
            if (b_der != 2 && b_izq == 2){
                cout<<"no garcias"<<endl;
                return false;
            }
            else{
                cout<<"garcias"<<endl;
                return true;
            }
        }
        cout<<"no garcias jaja salu2"<<endl;
        return false;
    }
};

// Function to check if given Binary Tree is Complete or not

#include <list>
bool isComplete(Node* root)
{
    // return if tree is empty
    if (root == nullptr)
        return false;

    // create an empty queue and enqueue root node
    list<Node*> queue;
    queue.push_back(root);

    // pointer to store current node
    Node* front = nullptr;

    // flag to mark end of full nodes
    bool flag = false;

    // run till queue is not empty
    while (queue.size())
    {
        // pop front node from the queue
        front = queue.front();
        queue.pop_front();

        // if we have encountered a non-full node before and current node
        // is not a leaf, tree cannot be complete tree
        if (flag && (front->izq || front->der))
                return false;

        // if izq child is empty & der child exists, tree cannot be complete
        if (front->izq == nullptr && front->der)
           return false;

        // if izq child exists, enqueue it
        if (front->izq)
           queue.push_back(front->izq);

        // if current node is a non-full node, set flag to true
        else
           flag = true;


        // if der child exists, enqueue it
        if (front->der)
           queue.push_back(front->der);

        // if current node is a non-full node, set flag to true
        else
           flag = true;
    }

    return true;
}


int main(){
	Node * start = new Node{2};
	//cout<<"lsxd";
	start->izq = new Node{3, new Node{5}, new Node{6}};
	start->der = new Node{4, nullptr, nullptr};

	Solutioner twat;
	cout << twat.isMinHeap(start) << endl;

}