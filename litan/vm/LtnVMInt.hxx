
#define BinaryInt(op)\
	const std::int64_t r = this->env.acc.popI();\
	const std::int64_t l = this->env.acc.popI();\
	this->env.acc.push(l op r);
