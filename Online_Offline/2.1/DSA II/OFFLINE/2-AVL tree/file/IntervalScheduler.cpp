#include <algorithm>
#include <chrono>
#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class IntervalNode
{
public:
    int id;
    int start;
    int end;
    int height;
    int maxEnd;
    IntervalNode *left;
    IntervalNode *right;

    IntervalNode(int eventId, int s, int e)
        : id(eventId), start(s), end(e), height(1), maxEnd(e), left(nullptr), right(nullptr) {}
};

class IntervalScheduler
{
private:
    IntervalNode *root;
    int nextId;
    unordered_map<int, pair<int, int>> events;

    int getHeight(IntervalNode *node) const
    {
        return node ? node->height : 0;
    }

    int getMaxEnd(IntervalNode *node) const
    {
        return node ? node->maxEnd : INT_MIN;
    }

    void updateNode(IntervalNode *node)
    {
        if (!node)
            return;
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        node->maxEnd = max(node->end, max(getMaxEnd(node->left), getMaxEnd(node->right)));
    }

    int getBalance(IntervalNode *node) const
    {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    static bool keyLess(int start1, int id1, int start2, int id2)
    {
        if (start1 != start2)
            return start1 < start2;
        return id1 < id2;
    }

    IntervalNode *rotateRight(IntervalNode *y)
    {
        IntervalNode *x = y->left;
        IntervalNode *middle = x->right;

        x->right = y;
        y->left = middle;

        updateNode(y);
        updateNode(x);
        return x;
    }

    IntervalNode *rotateLeft(IntervalNode *x)
    {
        IntervalNode *y = x->right;
        IntervalNode *middle = y->left;

        y->left = x;
        x->right = middle;

        updateNode(x);
        updateNode(y);
        return y;
    }

    IntervalNode *rebalance(IntervalNode *node)
    {
        if (!node)
            return nullptr;

        updateNode(node);
        int balance = getBalance(node);

        if (balance > 1)
        {
            if (getBalance(node->left) < 0)
            {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        if (balance < -1)
        {
            if (getBalance(node->right) > 0)
            {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    IntervalNode *insertNode(IntervalNode *node, int id, int s, int e)
    {
        if (!node)
            return new IntervalNode(id, s, e);

        if (keyLess(s, id, node->start, node->id))
        {
            node->left = insertNode(node->left, id, s, e);
        }
        else
        {
            node->right = insertNode(node->right, id, s, e);
        }

        return rebalance(node);
    }

    IntervalNode *minimumNode(IntervalNode *node) const
    {
        while (node && node->left)
            node = node->left;
        return node;
    }

    IntervalNode *eraseNode(IntervalNode *node, int s, int id)
    {
        if (!node)
            return nullptr;

        if (keyLess(s, id, node->start, node->id))
        {
            node->left = eraseNode(node->left, s, id);
        }
        else if (keyLess(node->start, node->id, s, id))
        {
            node->right = eraseNode(node->right, s, id);
        }
        else
        {
            if (!node->left || !node->right)
            {
                IntervalNode *child = node->left ? node->left : node->right;
                delete node;
                return child;
            }

            IntervalNode *successor = minimumNode(node->right);
            int successorStart = successor->start;
            int successorId = successor->id;

            node->id = successor->id;
            node->start = successor->start;
            node->end = successor->end;

            node->right = eraseNode(node->right, successorStart, successorId);
        }

        return rebalance(node);
    }

    static bool overlapsInterval(int aStart, int aEnd, int bStart, int bEnd)
    {
        return aStart < bEnd && bStart < aEnd;
    }

    bool anyConflict(IntervalNode *node, int s, int e) const
    {
        while (node)
        {
            if (overlapsInterval(node->start, node->end, s, e))
                return true;

            if (node->left && node->left->maxEnd > s)
            {
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }
        return false;
    }

    void collectOverlaps(IntervalNode *node, int s, int e, vector<int> &result) const
    {
        if (!node)
            return;

        if (node->left && node->left->maxEnd > s)
        {
            collectOverlaps(node->left, s, e, result);
        }

        if (overlapsInterval(node->start, node->end, s, e))
        {
            result.push_back(node->id);
        }

        if (node->start < e && node->right && node->right->maxEnd > s)
        {
            collectOverlaps(node->right, s, e, result);
        }
    }

    void collectAt(IntervalNode *node, int t, vector<int> &result) const
    {
        if (!node)
            return;

        if (node->left && node->left->maxEnd > t)
        {
            collectAt(node->left, t, result);
        }

        if (node->start <= t && t < node->end)
        {
            result.push_back(node->id);
        }

        if (node->start <= t && node->right && node->right->maxEnd > t)
        {
            collectAt(node->right, t, result);
        }
    }

    IntervalNode *nextNode(int t) const
    {
        IntervalNode *current = root;
        IntervalNode *answer = nullptr;

        while (current)
        {
            if (current->start >= t)
            {
                answer = current;
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        return answer;
    }

    string buildTreeString(IntervalNode *node) const
    {
        if (!node)
            return "";

        string result = to_string(node->id);
        if (node->left || node->right)
        {
            result += "(";
            result += buildTreeString(node->left);
            result += ",";
            result += buildTreeString(node->right);
            result += ")";
        }
        return result;
    }

    void clear(IntervalNode *node)
    {
        if (!node)
            return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    struct NextResult
    {
        bool found;
        int id;
        int start;
        int end;
    };

    IntervalScheduler() : root(nullptr), nextId(1) {}

    ~IntervalScheduler()
    {
        clear(root);
    }

    int add(int s, int e)
    {
        int id = nextId++;
        root = insertNode(root, id, s, e);
        events[id] = {s, e};
        return id;
    }

    bool remove(int id)
    {
        auto it = events.find(id);
        if (it == events.end())
            return false;

        int oldStart = it->second.first;
        root = eraseNode(root, oldStart, id);
        events.erase(it);
        return true;
    }

    bool update(int id, int s, int e)
    {
        auto it = events.find(id);
        if (it == events.end())
            return false;

        int oldStart = it->second.first;
        root = eraseNode(root, oldStart, id);
        root = insertNode(root, id, s, e);
        it->second = {s, e};
        return true;
    }

    bool conflict(int s, int e) const
    {
        return anyConflict(root, s, e);
    }

    vector<int> overlaps(int s, int e) const
    {
        vector<int> result;
        collectOverlaps(root, s, e, result);
        return result;
    }

    vector<int> at(int t) const
    {
        vector<int> result;
        collectAt(root, t, result);
        return result;
    }

    NextResult next(int t) const
    {
        IntervalNode *node = nextNode(t);
        if (!node)
            return {false, 0, 0, 0};
        return {true, node->id, node->start, node->end};
    }

    string treeString() const
    {
        return buildTreeString(root);
    }
};

struct TimingData
{
    long long count = 0;
    long long totalNs = 0;
};

static void addTiming(TimingData &data,
                      chrono::steady_clock::time_point start,
                      chrono::steady_clock::time_point stop)
{
    data.count++;
    data.totalNs += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
}

static void printTimingRow(const string &name, const TimingData &data)
{
    cout << name << "," << data.count << "," << data.totalNs << ",";
    if (data.count == 0)
        cout << "N/A\n";
    else
        cout << data.totalNs / data.count << "\n";
}

static void printIds(ofstream &output, const vector<int> &ids)
{
    if (ids.empty())
    {
        output << "none\n";
        return;
    }

    for (size_t i = 0; i < ids.size(); ++i)
    {
        if (i)
            output << ' ';
        output << ids[i];
    }
    output << '\n';
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <input-file> <output-file>\n";
        return 1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);
    if (!input || !output)
    {
        cerr << "Could not open input or output file.\n";
        return 1;
    }

    IntervalScheduler scheduler;
    TimingData addTime, removeTime, updateTime, conflictTime, overlapsTime, atTime, nextTime;

    string command;
    while (input >> command)
    {
        if (command == "ADD")
        {
            int s, e;
            input >> s >> e;

            auto begin = chrono::steady_clock::now();
            scheduler.add(s, e);
            auto finish = chrono::steady_clock::now();
            addTiming(addTime, begin, finish);

            output << scheduler.treeString() << '\n';
        }
        else if (command == "REMOVE")
        {
            int id;
            input >> id;

            auto begin = chrono::steady_clock::now();
            bool removed = scheduler.remove(id);
            auto finish = chrono::steady_clock::now();
            addTiming(removeTime, begin, finish);

            if (removed)
                output << scheduler.treeString() << '\n';
            else
                output << "not found\n";
        }
        else if (command == "UPDATE")
        {
            int id, s, e;
            input >> id >> s >> e;

            auto begin = chrono::steady_clock::now();
            bool updated = scheduler.update(id, s, e);
            auto finish = chrono::steady_clock::now();
            addTiming(updateTime, begin, finish);

            if (updated)
                output << scheduler.treeString() << '\n';
            else
                output << "not found\n";
        }
        else if (command == "CONFLICT")
        {
            int s, e;
            input >> s >> e;

            auto begin = chrono::steady_clock::now();
            bool found = scheduler.conflict(s, e);
            auto finish = chrono::steady_clock::now();
            addTiming(conflictTime, begin, finish);

            output << (found ? "yes" : "no") << '\n';
        }
        else if (command == "OVERLAPS")
        {
            int s, e;
            input >> s >> e;

            auto begin = chrono::steady_clock::now();
            vector<int> ids = scheduler.overlaps(s, e);
            auto finish = chrono::steady_clock::now();
            addTiming(overlapsTime, begin, finish);

            printIds(output, ids);
        }
        else if (command == "AT")
        {
            int t;
            input >> t;

            auto begin = chrono::steady_clock::now();
            vector<int> ids = scheduler.at(t);
            auto finish = chrono::steady_clock::now();
            addTiming(atTime, begin, finish);

            printIds(output, ids);
        }
        else if (command == "NEXT")
        {
            int t;
            input >> t;

            auto begin = chrono::steady_clock::now();
            IntervalScheduler::NextResult result = scheduler.next(t);
            auto finish = chrono::steady_clock::now();
            addTiming(nextTime, begin, finish);

            if (!result.found)
                output << "none\n";
            else
                output << result.id << ' ' << result.start << ' ' << result.end << '\n';
        }
    }

    cout << "operation,count,total_ns,average_ns\n";
    printTimingRow("add", addTime);
    printTimingRow("remove", removeTime);
    printTimingRow("update", updateTime);
    printTimingRow("conflict", conflictTime);
    printTimingRow("overlaps", overlapsTime);
    printTimingRow("at", atTime);
    printTimingRow("next", nextTime);

    return 0;
}
