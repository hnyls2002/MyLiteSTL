#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include "exceptions.hpp"

namespace sjtu {

/**
 * a container like std::priority_queue which is a heap internal.
 */
    template<typename T, class Compare = std::less<T>>
    class priority_queue {
    private:
        class node {
        public:
            T data;
            int dis;
            node *lc, *rc;

            explicit node(T _data, int _dis = 1, node *_lc = nullptr, node *_rc = nullptr) : data(_data), dis(_dis),
                                                                                             lc(_lc),
                                                                                             rc(_rc) {}

            node(const node &other) : data(other.data), dis(other.dis), lc(other.lc), rc(other.rc) {}
        };

        size_t siz;
        node *rt;

        Compare cmp;

        void balance_and_update_dis(node *o) {
            int dis_lc = o->lc == nullptr ? 0 : o->lc->dis;
            int dis_rc = o->rc == nullptr ? 0 : o->rc->dis;
            if (dis_lc < dis_rc)std::swap(o->lc, o->rc);
            o->dis = std::min(dis_lc, dis_rc) + 1;
        }

        void dfs_copy(node *&o1, node *o2) {
            if (o2 == nullptr)return;
            o1 = new node(*o2);
            dfs_copy(o1->lc, o2->lc);
            dfs_copy(o1->rc, o2->rc);
        }

        void dfs_destroy(node *o) {
            if (o == nullptr)return;
            dfs_destroy(o->lc), dfs_destroy(o->rc);
            delete o;
            o = nullptr;
        }

        node *dfs_merge(node *o1, node *o2) {
            if (o1 == nullptr)return o2;
            if (o2 == nullptr)return o1;
            if (cmp(o1->data, o2->data))std::swap(o1, o2);//merge o2 into o1
            //if (o2->data < o1->data)std::swap(o1, o2);//merge o2 into o1
            o1->rc = dfs_merge(o1->rc, o2);
            balance_and_update_dis(o1);
            return o1;
        }

    public:
        /**
         * TODO constructors
         */
        priority_queue(size_t _siz = 0, node *_rt = nullptr) : siz(_siz), rt(_rt) {}

        priority_queue(const priority_queue &other) : siz(other.siz) {
            dfs_copy(rt, other.rt);
        }

        /**
         * TODO deconstructor
         */
        ~priority_queue() {
            dfs_destroy(rt), siz = 0;
        }

        /**
         * TODO Assignment operator
         */
        priority_queue &operator=(const priority_queue &other) {
            if (this == &other)return *this;
            dfs_destroy(rt);
            siz = other.siz;
            dfs_copy(rt, other.rt);
            return *this;
        }

        /**
         * get the top of the queue.
         * @return a reference of the top element.
         * throw container_is_empty if empty() returns true;
         */
        const T &top() const {
            if (!siz)throw container_is_empty();
            return rt->data;
        }

        /**
         * TODO
         * push new element to the priority queue.
         */
        void push(const T &e) {
            node *o2 = new node(e);
            rt = dfs_merge(rt, o2);
            ++siz;
        }

        /**
         * TODO
         * delete the top element.
         * throw container_is_empty if empty() returns true;
         */
        void pop() {
            if (!siz)throw container_is_empty();
            node *tmp = rt;
            rt = dfs_merge(rt->lc, rt->rc);
            --siz;
            delete tmp;
        }

        /**
         * return the number of the elements.
         */
        size_t size() const {
            return siz;
        }

        /**
         * check if the container has at least an element.
         * @return true if it is empty, false if it has at least an element.
         */
        bool empty() const {
            return !siz;
        }

        /**
         * merge two priority_queues with at least O(logn) complexity.
         * clear the other priority_queue.
         */
        void merge(priority_queue &other) {
            rt = dfs_merge(rt, other.rt);
            other.rt = nullptr;
            siz += other.siz, other.siz = 0;
        }
    };

}

#endif
