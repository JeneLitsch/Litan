#pragma once
inline const char * std_container = R"###(
namespace std {
	build_in queue() const                      @ queue
	build_in stack() const                      @ stack
	build_in map() const                        @ map
	build_in array() const                      @ array
	
	build_in push(container, elem)              @ container_push
	build_in pop(container)                     @ container_pop
	build_in peek(container) const              @ container_peek
	build_in contains(map, key) const           @ container_contains
	build_in size(collection) const             @ container_size
	build_in empty(collection) const            @ container_empty
	build_in at(collection, i) const            @ container_at
	build_in front(collection) const            @ container_front
	build_in back(collection) const             @ container_back
	build_in insert_back(collection, element)   @ container_insert_back
	build_in insert_front(collection, element)  @ container_insert_front
	build_in insert(collection, index, element) @ container_insert
	build_in remove_back(collection)            @ container_remove_back
	build_in remove_front(collection)           @ container_remove_front
	build_in remove(collection, index)          @ container_remove
}
)###";
