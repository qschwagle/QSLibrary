#ifndef GAME_TFE_GAME_SQUARE_H
#define GAME_TFE_GAME_SQUARE_H

#include "game_tfe/box_dimension.h"
#include "geometry/geometry.h"

/**
 * A Game Square 
 *
 * Do to design choice of not having a virtual table, this class should never be inheritted by 
 * another class
 */
class GameSquare final {
    public:

        /** default constructor */
        GameSquare() : GameSquare(0) {}

        /** sets the value of the square to value
         *  \param value value of game square
         */
        GameSquare(int value);

        /** not copyable */
        GameSquare(const GameSquare&)=delete;

        /** not copyable */
        GameSquare& operator=(const GameSquare&)=delete;

        GameSquare(const GameSquare&& rhs) {
            mValue = std::move(rhs.mValue);
        }
        GameSquare& operator=(const GameSquare&& rhs) {
            mValue = std::move(rhs.mValue);
            mPosition = std::move(rhs.mPosition);
            return *this;
        }

        /**
         * tries to merge the two squares
         * \param lhs the square to merge to
         * \returns true if successful, false otherwise
         */
        bool TryMerge(GameSquare& lhs);

        /**
         * checks to see if two squares can be merged
         * \param lhs other square
         * \returns true if they can, false otherwise
         */
        bool CanMerge(const GameSquare& lhs);

        /**
         * can be skipped over
         * \returns true if this square can be skipped. otherwise false
         */
        [[nodiscard]] bool Skip(void) const noexcept { return mValue == 0; }

        /**
         * Gets the current position
         * \returns position of the square
         */
        RVector<2>& GetPosition(void) noexcept { return mPosition; }

        /**
         * Gets a constant position
         * \returns positon of the square
         */
        const RVector<2>& GetPosition(void) const noexcept { return mPosition; } 

        /**
         * set position of the square
         * \param position of the square
         */
        void SetPosition(const RVector<2>& position) { mPosition = position; }

        /**
         * Draw the square
         * \param out out geometry buffer
         * \param width width of the square
         */
        void Draw(Geometry<9>& out, float width);

    private:
        /// game square position
        RVector<2> mPosition;

        /// value of the square
        int mValue{0};
};

#endif
