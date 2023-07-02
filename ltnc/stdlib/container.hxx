#pragma once
inline const char * std_container = R"###(
namespace std {
	function queue() const
		=> build_in(queue)



	function queue(first, other...) {
		var queue = std::queue();
		std::push(queue, first);
		for(elem : other) std::push(queue, elem);
		return queue;
	}



	function stack() const
		=> build_in(stack)


	
	function stack(first, other...) {
		var stack = std::stack();
		std::push(stack, first);
		for(elem : other) std::push(stack, elem);
		return stack;
	}
	


	function map() const 
		=> [:]
	
	
	
	function array() const 
		=> []
	


	function push(container, elem)              
		=> build_in(container_push)
	
	
	
	function pop(container)                     
		=> build_in(container_pop)
	
	
	
	function peek(container) const              
		=> build_in(container_peek)
	
	
	
	function contains(map, key) const           
		=> build_in(container_contains)
	
	
	
	function size(collection) const             
		=> build_in(container_size)
	
	
	
	function empty(collection) const            
		=> build_in(container_empty)
	
	
	
	function at(collection, i) const            
		=> build_in(container_at)
	
	
	
	function front(collection) const            
		=> build_in(container_front)
	
	
	
	function back(collection) const             
		=> build_in(container_back)
	
	
	
	function insert_back(collection, element)   
		=> build_in(container_insert_back)
	
	
	
	function insert_front(collection, element)  
		=> build_in(container_insert_front)
	
	
	
	function insert(collection, index, element) 
		=> build_in(container_insert)
	
	
	
	function remove_back(collection)            
		=> build_in(container_remove_back)
	
	
	
	function remove_front(collection)           
		=> build_in(container_remove_front)
	
	
	
	function remove(collection, index)          
		=> build_in(container_remove)
}
)###";
