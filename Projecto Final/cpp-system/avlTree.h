#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <algorithm>
#include "avlNode.h"

using namespace std;

class AVLTree {

private:

    AVLNode* root;

    int height(AVLNode* node) {
        if(node == nullptr) return 0;
        return node->height;
    }

    int getBalance(AVLNode* node) {
        if(node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    AVLNode* rotateRight(AVLNode* y) {
        if(y == nullptr || y->left == nullptr) return y;

        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        if(x == nullptr || x->right == nullptr) return x;

        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    AVLNode* insertNode(AVLNode* node, Student* student) {
        if(node == nullptr) return new AVLNode(student);

        if(student->skill_score < node->student->skill_score) {
            node->left = insertNode(node->left, student);
        } else if(student->skill_score > node->student->skill_score) {
            node->right = insertNode(node->right, student);
        } else {
            if(student->student_id < node->student->student_id) {
                node->left = insertNode(node->left, student);
            } else if(student->student_id > node->student->student_id) {
                node->right = insertNode(node->right, student);
            } else {
                return node;
            }
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if(balance > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);

        if(balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if(balance < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);

        if(balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inorderTraversal(AVLNode* node) {
        if(node == nullptr) return;
        inorderTraversal(node->left);
        cout << node->student->skill_score << " - " << node->student->full_name << endl;
        inorderTraversal(node->right);
    }

    void traverseSilent(AVLNode* node) {
        if(node == nullptr) return;
        traverseSilent(node->left);
        traverseSilent(node->right);
    }

    Student* searchScore(AVLNode* node, int score) {
        if(node == nullptr) return nullptr;
        if(score == node->student->skill_score) return node->student;
        if(score < node->student->skill_score) return searchScore(node->left, score);
        return searchScore(node->right, score);
    }

public:

    AVLTree() {
        root = nullptr;
    }

    void insert(Student* student) {
        root = insertNode(root, student);
    }

    void showRanking() {
        cout << "\n=== RANKING ACADEMICO ===\n" << endl;
        inorderTraversal(root);
    }

    void showRankingSilent() {
        traverseSilent(root);
    }

    Student* search(int score) {
        return searchScore(root, score);
    }

    int getHeight() {
        return height(root);
    }
};

#endif