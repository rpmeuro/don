#include<iostream>
#include<vector>
#include<queue>
#include<omp.h>

using namespace std;

struct Node {
        int data;
        Node *left,*right;
};

Node* insert(Node* root,int data) {
        if(!root) {
                root = new Node{data,NULL,NULL};
                return root;
        }

        queue<Node*> q;
        q.push(root);

        while(!q.empty()) {

                Node* temp = q.front();
                q.pop();

                if(!temp->left){
                        temp->left = new Node{data,NULL,NULL};
                        return root;
                } else {
                        q.push(temp->left);
                }

                if(!temp -> right) {
                        temp -> right = new Node{data,NULL,NULL};
                        return root;
                } else {
                        q.push(temp-> right);
                }
        }
        return root;
}

void parallelBFS(Node *root) {
        if(!root) return;

        vector<Node*> currentLevel;
        currentLevel.push_back(root);

        while(!currentLevel.empty()) {
                vector<Node*> nextLevel;

                #pragma omp parallel
                {
                        vector<Node*> localNext;

                        #pragma omp for
                        for(int i=0;i < currentLevel.size();i++) {
                                Node* curr = currentLevel[i];

                                #pragma omp critical
                                cout<<curr->data<<" ";

                                if(curr->left) localNext.push_back(curr->left);
                                if(curr->right) localNext.push_back(curr->right);
                        }

                        #pragma omp critical
                        nextLevel.insert(nextLevel.end(),localNext.begin(),localNext.end());
                }
                currentLevel = nextLevel;
        }
}


int main() {
        Node *root = NULL;
        int data;
        char ch;

        do {
                cout<<"Enter Data : ";
                cin>>data;
                root = insert(root,data);

                cout<<"Add more nodes (y/n)";
                cin>>ch;
        } while(ch=='y' || ch == 'Y');
        cout<<"\n Parallel BFS Traversal : \n";
        parallelBFS(root);
        return 0;
}
