#include <bits/stdc++.h>
using namespace std;

namespace LIST {

struct NODE {
    int val;
    NODE* prev;
    NODE* next;
};

static NODE* head = nullptr;
static NODE* tail = nullptr;
static int len = 0;

void Pre() {
    head = nullptr;
    tail = nullptr;
    len = 0;
}

static NODE* move_to(int i) {
    if (i < 0 || i >= len) return nullptr;
    if (i < len / 2) {
        NODE* cur = head;
        for (int idx = 0; idx < i; ++idx) cur = cur->next;
        return cur;
    } else {
        NODE* cur = tail;
        for (int idx = len - 1; idx > i; --idx) cur = cur->prev;
        return cur;
    }
}

void insert(int i, int x) {
    // Insert so that new node is at position i (0-based)
    NODE* node = new NODE{ x, nullptr, nullptr };
    if (len == 0) {
        head = tail = node;
        len = 1;
        return;
    }
    if (i <= 0) {
        // insert at head
        node->next = head;
        head->prev = node;
        head = node;
    } else if (i >= len) {
        // insert at tail (after current tail)
        node->prev = tail;
        tail->next = node;
        tail = node;
    } else {
        NODE* pos = move_to(i); // current element at i
        // insert before pos
        node->next = pos;
        node->prev = pos->prev;
        if (pos->prev) pos->prev->next = node;
        pos->prev = node;
        if (i == 0) head = node; // safety, though handled above
    }
    ++len;
}

void remove(int i) {
    if (len == 0) return; // problem guarantees valid ops, but guard anyway
    if (i <= 0) {
        NODE* del = head;
        if (!del) return;
        head = del->next;
        if (head) head->prev = nullptr; else tail = nullptr;
        delete del;
    } else if (i >= len - 1) {
        NODE* del = tail;
        if (!del) return;
        tail = del->prev;
        if (tail) tail->next = nullptr; else head = nullptr;
        delete del;
    } else {
        NODE* del = move_to(i);
        if (!del) return;
        del->prev->next = del->next;
        del->next->prev = del->prev;
        delete del;
    }
    --len;
}

int Get_length() { return len; }

int Query(int i) {
    if (i < 0 || i >= len) return -1;
    NODE* p = move_to(i);
    if (!p) return -1;
    return p->val;
}

void Print() {
    if (len == 0) {
        cout << -1 << '\n';
        return;
    }
    NODE* cur = head;
    bool first = true;
    while (cur) {
        if (!first) cout << ' ';
        cout << cur->val;
        first = false;
        cur = cur->next;
    }
    cout << '\n';
}

void Clear() {
    NODE* cur = head;
    while (cur) {
        NODE* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    head = tail = nullptr;
    len = 0;
}

} // namespace LIST

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; if (!(cin >> n)) return 0;
    LIST::Pre();
    for (int _ = 0; _ < n; ++_) {
        int op; cin >> op;
        if (op == 0) {
            cout << LIST::Get_length() << '\n';
        } else if (op == 1) {
            int p, x; cin >> p >> x;
            LIST::insert(p, x);
        } else if (op == 2) {
            int p; cin >> p;
            cout << LIST::Query(p) << '\n';
        } else if (op == 3) {
            int p; cin >> p;
            LIST::remove(p);
        } else if (op == 4) {
            LIST::Print();
        }
    }
    LIST::Clear();
    return 0;
}

