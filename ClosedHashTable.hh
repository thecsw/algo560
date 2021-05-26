#ifndef HASH_HH
#define HASH_HH

class ClosedHashTable {
private:
        // Storing actual values here
        int* _arr;
        // Flags to mark cells' lives
        bool* _fl;
        // The load factor
        int _load;
        // The size
        int _size;
        // This is the hash function
        int _h(int) const;
        // This is the super hash function, so
        // super_h(x, k) = (h(x) + f(k)) mod m
        int _super_h(int, int) const;
        // False to use quadratic resolution, True for doubleH
        bool _use_quad;
        // This is the quadratic collision resolution
        int _f_quad(int) const;
        // This is the double hashing resolution
        int _f_doub(int, int) const;
        // This is the rehash function
        void _rehash();
        // Rehash threshold, so load factor is 1/_max_load,
        // this is done so we don't do float arithmetic
        int _max_load_frac_denom;
public:
        ClosedHashTable(int);
        ~ClosedHashTable();

        void Insert(int);
	void Delete(int);
	int Find(int) const;
        void Print() const;

        // This will set _use_quad to true
        void UseDoubleHashing();
};

#endif // HASH_HH
