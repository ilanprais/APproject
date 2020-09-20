#pragma once

namespace searcher {

    template <typename Identifier>
    class Element {

        Identifier m_identifier;
        double m_value;

        public:

            Element(const Identifier& identifier, const double value)
            : m_identifier(identifier),
            m_value(value) {}

            const Identifier& getIdentifier() const {
                return m_identifier;
            }

            double getValue() const {
                return m_value;
            }

            bool operator==(const Element<Identifier>& other) const {
                return m_identifier == other.m_identifier && m_value == other.m_value;
            }

            bool operator!=(const Element<Identifier>& other) const {
                return !(*this == other);
            }
    };

    template <typename Identifier>
    struct CompareByIdentifier {
        
        bool operator()(const Element<Identifier>& e1, const Element<Identifier>& e2) const {
                    return e1.getIdentifier() < e2.getIdentifier();
        }
    };

    template <typename Identifier>
    struct CompareByFScore {

        const Element<Identifier> m_goal;

        CompareByFScore(const Element<Identifier>& goal)
        : m_goal(goal) {}

        bool operator()(const Element<Identifier>& e1, const Element<Identifier>& e2) const;
    };
}