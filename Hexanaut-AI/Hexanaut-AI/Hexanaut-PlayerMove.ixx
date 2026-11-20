export module Hexanaut:PlayerMove;

// This struct represents a move made by a player. It is immutable.
// In Hexanaut, the player can only decide on the direction it's moving. The speed is determined by other game mechanics.
export struct PlayerMove {
    // The absolute direction expressed as an angle in radians in counter-clockwise direction where 0 radians points to the right
    double turn_angle_radians;
};
