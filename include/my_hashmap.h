#ifndef __MY_HASHMAP_HEADER_FILE__
#define __MY_HASHMAP_HEADER_FILE__

#include <functional>
namespace mystl {

template<typename Key, typename Value, typename Hash = std::hash<Key>>
class MyHashMap {
public:
    using KeyValuePair = std::pair<Key, Value>;

private:
    std::vector<std::list<KeyValuePair>> buckets_;
    size_t size_;
    float max_load_factor_;
    Hash hash_func_;

    size_t get_bucket_index(const Key& key) {
        // whatever the hash value is, calculate it as one reasonable id of buckets_
        return hash_func_(key) % buckets_.size();
    }

    void rehash(size_t new_capacity) {
        std::vector<std::list<KeyValuePair>> new_buckets;
        for(const auto& bucket : buckets_) {
            for(const auto& pair : bucket) {
                size_t new_index = hash_func_(pair.first) % new_capacity;
                new_buckets[new_index].push_back(pair);
            }
        }

        buckets_ = std::move(new_buckets);
    }
public:
    // std::vector<int> a(5); -> 5 elements with value 0
    // buckets_(initial_sz) -> 16 empty list (buckets)
    explicit MyHashMap(size_t initial_sz = 16, float max_load_factor = 0.75f)
        :buckets_(initial_sz), size_(0), max_load_factor_(max_load_factor){}
    ~MyHashMap() = default;
};

}

#endif
