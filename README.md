# Hemingway

> Implementations of the classic and covering locality-sensitive hashing schemes for Hamming space

[![Build Status](https://semaphoreci.com/api/v1/kasperisager/hemingway/branches/master/badge.svg)](https://semaphoreci.com/kasperisager/hemingway)

Hemingway is a library for performing nearest-neighbour searches in datasets consisting of high-dimensional bit vectors using locality-sensitive hashing. Two flavors of LSH are currently supported: Classic LSH, originally described by [Piotr Indyk and Rajeev Motwani](http://dl.acm.org/citation.cfm?id=276876), and Covering LSH, a newer construction by [Rasmus Pagh](http://dl.acm.org/citation.cfm?id=2884436). You can read our paper on the library [here](paper.pdf).

As for the name? Say the words "locality-sensitive hashing" and "Hamming space" fast enough a bunch of times and you'll eventually arrive at "Hemingway". If not, you probably _didn't pick appropriate parameters_.

## Contents

-   [Installation](#installation)
-   [Usage](#usage)
-   [API](#api)
-   [Authors](#authors)
-   [License](#license)

## Installation

Hemingway can be built using any compiler that supports C++11. A [tup](http://gittup.org/tup)-based pipeline is included and is the recommended way to build Hemingway. Start by downloading and installing tup and then run the following from the root of the library:

```console
$ CXX=<compiler> tup
```

This will compile the implementation files to `src/lsh.a`. Grab this along with the header files and you'll be all set! You can check out the next section for a guide on how to actually use the library.

## Usage

The design of Hemingway is fairly simple in that it exposes only two classes for all your LSH needs: `lsh::vector` and `lsh::table`. The `lsh::vector` class is used for representing bit vectors of arbitrary dimensionality and is constructed by supplying a `std::vector<bool>` containing the components of the vector:

```cpp
lsh::vector v({1, 0, 0, 0, 1, 1, 0, 1});
```

The `lsh::table` class is used for representing a lookup table containing partitions of vector buckets. Two LSH schemes are currently supported in lookup tables:

__Classic:__ In this scheme, vectors are hashed into buckets using random bit masks associated with each partition. When constructing this table, 3 parameters are specified: The dimensionality of input vectors, the number of bits to sample from vectors, and the number of partitions to use:

```cpp
lsh::table t({.dimensions = 8, .samples = 3, .partitions = 4);
```

__Covering:__ In this scheme, vectors are hashed into buckets using carefully constructed bit masks that ensure that the hashes of vectors within a given radius from each other will collide. Only two parameters are specified when constructing this table: The dimensionality of input vectors, and the radius that should be covered:

```cpp
lsh::table t({.dimensions = 8, .radius = 2);
```

Once you've constructed your table, go ahead and add your vectors:

```cpp
t.insert(v);
```

Once you've added all your vectors you can perform queries against the lookup table:

```cpp
lsh::vector r = t.query(lsh::vector({1, 0, 1, 0, 1, 1, 0, 0}));
```

## Authors

This library came about as a result of the Advanced Algorithms seminar held at the IT University of Copenhagen. We would like to give thanks to our supervisors for not only their help but also their immense patience during the seminar.

[<img src=https://github.com/kasperisager.png width=125>](http://github.com/kasperisager) | [<img src=https://github.com/Nemeczek.png width=125>](http://github.com/Nemeczek)
--- | ---
[Kasper Kronborg Isager](http://github.com/kasperisager) | [Radosław Niemczyk](http://github.com/Nemeczek)

## License

Copyright &copy; 2016 [Kasper Kronborg Isager](https://github.com/kasperisager)
and [Radosław Niemczyk](https://github.com/Nemeczek). Licensed under the terms of the [MIT license](LICENSE.md).
