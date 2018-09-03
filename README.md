# roda

`roda` adalah pustaka untuk iterator dan algorithm.

Interface iterator `roda` adalah sebagai berikut.
```
interface Iterator {

  // next
  Iterator&
  operator++()

  // has next?
  explicit operator bool() const;

  // get current value
  Reference operator*() const;
};
```

`roda` dibuat untuk mengaplikasikan Iterator Design Pattern.
Berbeda dengan iterator pada _library standart_ C++ yang menggunakan dua iterator untuk `begin` dan `end`.

contoh `roda` vs `std`

`std`
```
std::vector<int> v{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };

int target1 = 3;
int target2 = 5;
int num_items1 = std::count(v.begin(), v.end(), target1);
int num_items2 = std::count(v.begin(), v.end(), target2);
std::cout << "number: " << target1 << " count: " << num_items1 << '\n';
std::cout << "number: " << target2 << " count: " << num_items2 << '\n';

// use a lambda expression to count elements divisible by 3.
int num_items3 = std::count_if(v.begin(), v.end(), [](int i){return i % 3 == 0;});
std::cout << "number divisible by three: " << num_items3 << '\n';
```

`roda`
```
std::vector<int> v{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };
auto it = roda::RangeIterator{v};

int target1 = 3;
int target2 = 5;
auto num_items1 = roda::count(it, target1);
auto num_items2 = roda::count(it, target2);
std::cout << "number: " << target1 << " count: " << num_items1 << '\n';
std::cout << "number: " << target2 << " count: " << num_items2 << '\n';

// use a lambda expression to count elements divisible by 3.
auto num_items3 = roda::count_if(it, [](int i) { return i % 3 == 0; });
std::cout << "number divisible by three: " << num_items3 << '\n';
```


