#pragma once
#include <optional>
#include <memory>
namespace ltnc {
	struct Type;
	
	class ArrayContainer {
	public:
		ArrayContainer(const Type & type) {
			this->type = std::make_shared<Type>(type);
		}
		virtual ~ArrayContainer() {}
		const Type & get() const {
			return *this->type;
		}
	private:
		std::shared_ptr<Type> type;
	};


	struct Type {
		enum Variation {VOI, INT, FLT, ARR} type;
		
		Type(Variation type) : type(type) {}
		
		Type() : type(VOI) {}

		inline bool operator==(Variation type) const {
			return this->type == type;
		}

		inline bool operator==(Type other) const {
			return this->type == other.type;
		}
		std::optional<ArrayContainer> arrayType;

	};

}