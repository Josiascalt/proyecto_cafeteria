#include "domain.hpp"

#include <string>
#include <string_view>
#include <utility>
#include <variant>
#include <unordered_map>
#include <filesystem>

#include <iostream>

namespace catalogue {
    namespace domain {
        namespace literals {
            std::filesystem::path operator""_p(const char* pathname, Size size) {
                return std::filesystem::path(pathname, pathname + size);
            }
        } //namespace literals

        namespace components {
            namespace types {
                //class Group member functions definition
                bool Group::IsTAC() const {
                    return std::holds_alternative<TAC>(group_);
                }

                bool Group::IsTAIS() const {
                    return std::holds_alternative<TAIS>(group_);
                }

                bool Group::IsTAA() const {
                    return std::holds_alternative<TAA>(group_);
                }

                Group::TAC Group::GetAsTAC() const {
                    return std::get<TAC>(group_);
                }

                Group::TAIS Group::GetAsTAIS() const {
                    return std::get<TAIS>(group_);
                }

                Group::TAA Group::GetAsTAA() const {
                    return std::get<TAA>(group_);
                }

                bool Group::operator==(const Group& other) const {
                    return group_ == other.group_;
                }

                bool Group::operator!=(const Group& other) const {
                    return !(*this == other);
                }
            }//namespace types
        } //namespace components
        
        namespace compound_types {
        } //namespace compound_types
    } // namespace domain
} // namespace catalogue


