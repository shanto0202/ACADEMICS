#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <chrono>

using namespace std;

class Node {
public:
    int id;
    int start;
    int end;
    int height;
    int maxEnd;

    Node* left;
    Node* right;

    Node(int i, int s, int e) {
        id = i;
        start = s;
        end = e;
        height = 1;
        maxEnd = e;
        left = nullptr;
        right = nullptr;
    }
};

class Scheduler {
public:
    Node* root;
    int nextId;
    unordered_map<int, pair<int, int>> events;

    Scheduler() {
        root = nullptr;
        nextId = 1;
    }

    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int maxEnd(Node* node) {
        if (node == nullptr) {
            return -2147483647;
        }
        return node->maxEnd;
    }

    int balance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    void update(Node* node) {
        if (node == nullptr) {
            return;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        node->maxEnd = max(node->end, max(maxEnd(node->left), maxEnd(node->right)));
    }

    bool lessThan(int start1, int id1, int start2, int id2) {
        if (start1 != start2) {
            return start1 < start2;
        }
        return id1 < id2;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* temp = x->right;

        x->right = y;
        y->left = temp;

        update(y);
        update(x);

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* temp = y->left;

        y->left = x;
        x->right = temp;

        update(x);
        update(y);

        return y;
    }

    Node* balanceTree(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        update(node);

        int b = balance(node);

        if (b > 1) {
            if (balance(node->left) < 0) {
                node->left = leftRotate(node->left);
            }
            return rightRotate(node);
        }

        if (b < -1) {
            if (balance(node->right) > 0) {
                node->right = rightRotate(node->right);
            }
            return leftRotate(node);
        }

        return node;
    }

    Node* insertNode(Node* node, int id, int start, int end) {
        if (node == nullptr) {
            return new Node(id, start, end);
        }

        if (lessThan(start, id, node->start, node->id)) {
            node->left = insertNode(node->left, id, start, end);
        }
        else {
            node->right = insertNode(node->right, id, start, end);
        }

        return balanceTree(node);
    }

    Node* minimum(Node* node) {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* deleteNode(Node* node, int start, int id) {
        if (node == nullptr) {
            return nullptr;
        }

        if (lessThan(start, id, node->start, node->id)) {
            node->left = deleteNode(node->left, start, id);
        }
        else if (lessThan(node->start, node->id, start, id)) {
            node->right = deleteNode(node->right, start, id);
        }
        else {
            if (node->left == nullptr || node->right == nullptr) {
                Node* child = (node->left != nullptr) ? node->left : node->right;
                delete node;
                return child;
            }

            Node* successor = minimum(node->right);

            node->id = successor->id;
            node->start = successor->start;
            node->end = successor->end;

            node->right = deleteNode(
                node->right,
                successor->start,
                successor->id
            );
        }

        return balanceTree(node);
    }

    bool overlap(int start1, int end1, int start2, int end2) {
        return start1 < end2 && start2 < end1;
    }

    bool conflictSearch(Node* node, int start, int end) {
        while (node != nullptr) {
            if (overlap(node->start, node->end, start, end)) {
                return true;
            }

            if (node->left != nullptr && node->left->maxEnd > start) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }

        return false;
    }

    void overlapSearch(Node* node, int start, int end, vector<int>& result) {
        if (node == nullptr) {
            return;
        }

        if (node->left != nullptr && node->left->maxEnd > start) {
            overlapSearch(node->left, start, end, result);
        }

        if (overlap(node->start, node->end, start, end)) {
            result.push_back(node->id);
        }

        if (node->right != nullptr &&
            node->start < end &&
            node->right->maxEnd > start) {
            overlapSearch(node->right, start, end, result);
        }
    }

    void atSearch(Node* node, int time, vector<int>& result) {
        if (node == nullptr) {
            return;
        }

        if (node->left != nullptr && node->left->maxEnd > time) {
            atSearch(node->left, time, result);
        }

        if (node->start <= time && time < node->end) {
            result.push_back(node->id);
        }

        if (node->right != nullptr &&
            node->start <= time &&
            node->right->maxEnd > time) {
            atSearch(node->right, time, result);
        }
    }

    Node* findNext(int time) {
        Node* current = root;
        Node* answer = nullptr;

        while (current != nullptr) {
            if (current->start >= time) {
                answer = current;
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        return answer;
    }

    void add(int start, int end) {
        int id = nextId++;
        root = insertNode(root, id, start, end);
        events[id] = {start, end};
    }

    bool remove(int id) {
        if (events.find(id) == events.end()) {
            return false;
        }

        int start = events[id].first;
        root = deleteNode(root, start, id);
        events.erase(id);

        return true;
    }

    bool updateEvent(int id, int start, int end) {
        if (events.find(id) == events.end()) {
            return false;
        }

        int oldStart = events[id].first;
        root = deleteNode(root, oldStart, id);
        root = insertNode(root, id, start, end);

        events[id] = {start, end};

        return true;
    }

    bool conflict(int start, int end) {
        return conflictSearch(root, start, end);
    }

    vector<int> overlaps(int start, int end) {
        vector<int> result;
        overlapSearch(root, start, end, result);
        return result;
    }

    vector<int> at(int time) {
        vector<int> result;
        atSearch(root, time, result);
        return result;
    }

    string treeString(Node* node) {
        if (node == nullptr) {
            return "";
        }

        string result = to_string(node->id);

        if (node->left != nullptr || node->right != nullptr) {
            result += "(";
            result += treeString(node->left);
            result += ",";
            result += treeString(node->right);
            result += ")";
        }

        return result;
    }

    void clear(Node* node) {
        if (node == nullptr) {
            return;
        }

        clear(node->left);
        clear(node->right);
        delete node;
    }

    ~Scheduler() {
        clear(root);
    }
};

void printVector(ofstream& output, vector<int>& result) {
    if (result.empty()) {
        output << "none\n";
        return;
    }
    
    sort(result.begin(), result.end());

    for (int i = 0; i < (int)result.size(); i++) {
        if (i > 0) {
            output << " ";
        }
        output << result[i];
    }

    output << "\n";
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        return 1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    if (!input || !output) {
        return 1;
    }

    Scheduler scheduler;

    long long addTotal = 0;
    long long removeTotal = 0;
    long long updateTotal = 0;
    long long conflictTotal = 0;
    long long overlapsTotal = 0;
    long long atTotal = 0;
    long long nextTotal = 0;

    int addCount = 0;
    int removeCount = 0;
    int updateCount = 0;
    int conflictCount = 0;
    int overlapsCount = 0;
    int atCount = 0;
    int nextCount = 0;

    string command;

    while (input >> command) {
        if (command == "ADD") {
            int startTime;
            int endTime;

            input >> startTime >> endTime;

            auto start = chrono::high_resolution_clock::now();
            scheduler.add(startTime, endTime);
            auto finish = chrono::high_resolution_clock::now();

            addTotal += chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            addCount++;

            output << scheduler.treeString(scheduler.root) << "\n";
        }

        else if (command == "REMOVE") {
            int id;
            input >> id;

            auto start = chrono::high_resolution_clock::now();
            bool ok = scheduler.remove(id);
            auto finish = chrono::high_resolution_clock::now();

            removeTotal += chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            removeCount++;

            if (ok) {
                output << scheduler.treeString(scheduler.root) << "\n";
            }
            else {
                output << "not found\n";
            }
        }

        else if (command == "UPDATE") {
            int id;
            int startTime;
            int endTime;

            input >> id >> startTime >> endTime;

            auto start = chrono::high_resolution_clock::now();
            bool ok = scheduler.updateEvent(id, startTime, endTime);
            auto finish = chrono::high_resolution_clock::now();

            updateTotal += chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            updateCount++;

            if (ok) {
                output << scheduler.treeString(scheduler.root) << "\n";
            }
            else {
                output << "not found\n";
            }
        }

        else if (command == "CONFLICT") {
            int startTime;
            int endTime;

            input >> startTime >> endTime;

            auto start = chrono::high_resolution_clock::now();
            bool ok = scheduler.conflict(startTime, endTime);
            auto finish = chrono::high_resolution_clock::now();

            conflictTotal += chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            conflictCount++;

            if (ok) {
                output << "yes\n";
            }
            else {
                output << "no\n";
            }
        }

        else if (command == "OVERLAPS") {
            int startTime;
            int endTime;

            input >> startTime >> endTime;

            auto start = chrono::high_resolution_clock::now();
            vector<int> result = scheduler.overlaps(startTime, endTime);
            auto finish = chrono::high_resolution_clock::now();

            overlapsTotal += chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            overlapsCount++;

            printVector(output, result);
        }

        else if (command == "AT") {
            int time;

            input >> time;

            auto start = chrono::high_resolution_clock::now();
            vector<int> result = scheduler.at(time);
            auto finish = chrono::high_resolution_clock::now();

            atTotal += chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            atCount++;

            printVector(output, result);
        }

        else if (command == "NEXT") {
            int time;

            input >> time;

            int id = -1;
            int startTime = 0;
            int endTime = 0;

            auto start = chrono::high_resolution_clock::now();
            Node* node = scheduler.findNext(time);

            if (node != nullptr) {
                id = node->id;
                startTime = node->start;
                endTime = node->end;
            }

            auto finish = chrono::high_resolution_clock::now();

            nextTotal += chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            nextCount++;

            if (node != nullptr) {
                output << id << " " << startTime << " " << endTime << "\n";
            }
            else {
                output << "none\n";
            }
        }
    }

    cout << "operation,count,total_ns,average_ns\n";

    if (addCount > 0) {
        cout << "add," << addCount << "," << addTotal << "," << addTotal / addCount << "\n";
    }

    if (removeCount > 0) {
        cout << "remove," << removeCount << "," << removeTotal << "," << removeTotal / removeCount << "\n";
    }

    if (updateCount > 0) {
        cout << "update," << updateCount << "," << updateTotal << "," << updateTotal / updateCount << "\n";
    }

    if (conflictCount > 0) {
        cout << "conflict," << conflictCount << "," << conflictTotal << "," << conflictTotal / conflictCount << "\n";
    }

    if (overlapsCount > 0) {
        cout << "overlaps," << overlapsCount << "," << overlapsTotal << "," << overlapsTotal / overlapsCount << "\n";
    }

    if (atCount > 0) {
        cout << "at," << atCount << "," << atTotal << "," << atTotal / atCount << "\n";
    }

    if (nextCount > 0) {
        cout << "next," << nextCount << "," << nextTotal << "," << nextTotal / nextCount << "\n";
    }

    return 0;
}