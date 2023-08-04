# Iterator Invalidation

Adding or removing elements from a container invalidates iterators pointing into that container.
If a invalidated iterator is used an exception in thrown.

Currently these containers are affected

- Map