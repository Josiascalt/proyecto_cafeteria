#include "domain.hpp"

#include <string>
#include <string_view>
#include <utility>
#include <memory>
#include <variant>
#include <filesystem>

namespace catalogue {
    namespace domain {
        namespace literals {
            std::filesystem::path operator""_p(const char* pathname, size_t size) {
                return std::filesystem::path(pathname, pathname + size);
            }
        } //namespace literals

        //class Components member functions definition
        bool Components::HasName() const {
            return has_name_;
        }

        bool Components::HasIdentifier() const {
            return has_identifier_;
        }

        bool Components::HasGender() const {
            return has_gender_;
        }

        bool Components::HasGroup() const {
            return has_group_;
        }

        //class Components::Group member functions definition
        bool Components::Group::IsInitialized() const {
            return !std::holds_alternative<std::monostate>(*this);
        }

        bool Components::Group::IsTAC() const {
            return std::holds_alternative<groups::TAC>(*this);
        }

        bool Components::Group::IsTAIS() const {
            return std::holds_alternative<groups::TAIS>(*this);
        }

        bool Components::Group::IsTAA() const {
            return std::holds_alternative<groups::TAA>(*this);
        }

        groups::TAC Components::Group::GetAsTAC() const {
            return std::get<groups::TAC>(*this);
        }

        groups::TAIS Components::Group::GetAsTAIS() const {
            return std::get<groups::TAIS>(*this);
        }

        groups::TAA Components::Group::GetAsTAA() const {
            return std::get<groups::TAA>(*this);
        }

    } // namespace domain
} // namespace catalogue


