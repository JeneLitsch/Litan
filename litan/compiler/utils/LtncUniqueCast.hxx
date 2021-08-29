#include <memory>

template<class To, class From>
std::unique_ptr<To> dynamic_unique_cast(std::unique_ptr<From> && ptr) {
	if(To * to = dynamic_cast<To*>(ptr.get())) {
		ptr.release();
		return std::unique_ptr<To>(to);
	}
	else {
		return nullptr;
	}
}