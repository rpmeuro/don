#include<iostream>
#include<queue>
#include<omp.h>
using namespace std;


struct Node {
        int data;
        Node *left,*right;
};

Node *insert(Node* root,int data) {
        if(!root) {
                root = new Node{data,NULL,NULL};
                return root;
        }

        queue<Node*> q;
        q.push(root);

        while(!q.empty()) {
                Node *temp = q.front();
                q.pop();

                if(!temp->left) {
                        temp->left = new Node{data,NULL,NULL};
                        return root;
                } else {
                        q.push(temp->left);
                }

                if(!temp->right) {
                        temp->right = new Node{data,NULL,NULL};
                        return root;
                } else {
                        q.push(temp->right);
                }
        }
        return root;
}

void bfs(Node *root) {
        queue<Node*> q;
        q.push(root);

        while(!q.empty()) {
                int size = q.size();

                #pragma omp parallel for
                for(int i=0;i<size;i++) {
                        Node* curr;

                        #pragma omp critical
                        {
                                curr = q.front();
                                q.pop();
                                cout<<curr->data<<" ";
                        }

                        #pragma omp critical

                        {
                                if(curr->left) q.push(curr->left);
                                if(curr->right) q.push(curr->right);
                        }
                }
        }
}


int main() {
        int data;
        char ch;
        Node *root=NULL;

        do{
                cout<<"Enter Data : ";
                cin>>data;
                root = insert(root,data);
                cout<<"Add more nodes : ";
                cin>>ch;
        } while(ch == 'y' || ch=='Y');

        cout<<"BFS Traversal : "<<endl;

        bfs(root);
        return 0;
}
