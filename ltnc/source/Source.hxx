#pragma once
#include <string>
#include <istream>
#include <fstream>
#include <vector>
#include <memory>

namespace ltn::c {
	class Source final {

		struct SourceConcept {
			virtual std::unique_ptr<std::istream> make_istream() const = 0;
			virtual std::string get_name() const = 0; 
			virtual std::string get_full_name() const = 0;
			virtual std::unique_ptr<SourceConcept> clone() const = 0;
			virtual std::vector<Source> get_module_subsources() const = 0;
			virtual ~SourceConcept() = default;
		};



		template<typename T>
		struct SourceModel : SourceConcept {
			SourceModel(const T & t)
				: t {t} {}

			virtual std::unique_ptr<std::istream> make_istream() const override {
				return t.make_istream();
			}

			virtual std::string get_name() const override {
				return t.get_name();
			} 

			virtual std::string get_full_name() const override {
				return t.get_full_name();
			}

			virtual std::vector<Source> get_module_subsources() const override {
				return t.get_module_subsources();
			}

			virtual std::unique_ptr<SourceConcept> clone() const override {
				return std::make_unique<SourceModel<T>>(t);
			}

			T t;
		};



	public:

		template<typename T>
		Source (const T & t)
			: impl { std::make_unique<SourceModel<T>>(t) } {}



		Source(const Source & other) {
			this->impl = other.impl->clone();
		} 



		Source operator=(const Source & other) {
    		Source temp{other};
    		this->swap(temp);
			return *this;
		}



		Source(Source && other) {
			this->impl = std::move(other.impl);
		} 



		Source operator=(Source && other) {
    		this->swap(other);
			return *this;
		}



		~Source() = default;



		void swap(Source & other) {
			std::swap(this->impl, other.impl);
		}



		std::unique_ptr<std::istream> make_istream() const {
			return impl->make_istream();
		}



		std::string get_name() const {
			return impl->get_name();
		} 



		std::string get_full_name() const {
			return impl->get_full_name();
		}



		std::vector<Source> get_module_subsources() const {
			return impl->get_module_subsources();
		}



	private:
		std::unique_ptr<SourceConcept> impl;
	};
}