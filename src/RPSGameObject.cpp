#include "RPSGameObject.h"
#include "environment.h"
#include "iconFactory.h"

bool RPSGameObject::intersect(ICollider *other) {
	auto *otherObj = dynamic_cast<RPSGameObject *>(other);
	if ( !otherObj ) {
		return false;
	}

	return _pos.x() == otherObj->_pos.x() && _pos.y() == otherObj->_pos.y();
}

void RPSGameObject::onCollision(ICollider *other) {
	auto *otherObj = dynamic_cast<RPSGameObject *>(other);
	if ( !otherObj )
		return;

	RPSType self = this->getType();
	RPSType enemy = otherObj->getType();

	// 被剋就轉型
	if ( (self == RPSType::ROCK && enemy == RPSType::PAPER) ||
	     (self == RPSType::PAPER && enemy == RPSType::SCISSORS) ||
	     (self == RPSType::SCISSORS && enemy == RPSType::ROCK) ) {
		this->setType(enemy);
	}

	switch ( _dir ) {
	case Direction::UP:
		_dir = Direction::DOWN;
		break;
	case Direction::DOWN:
		_dir = Direction::UP;
		break;
	case Direction::LEFT:
		_dir = Direction::RIGHT;
		break;
	case Direction::RIGHT:
		_dir = Direction::LEFT;
		break;
	case Direction::TOP_LIFT:
		_dir = Direction::DOWN_RIGHT;
		break;
	case Direction::TOP_RIGHT:
		_dir = Direction::DOWN_LIFT;
		break;
	case Direction::DOWN_LIFT:
		_dir = Direction::TOP_RIGHT;
		break;
	case Direction::DOWN_RIGHT:
		_dir = Direction::TOP_LIFT;
		break;
	}
}

void RPSGameObject::update() {
	int nextX = _pos.x();
	int nextY = _pos.y();

	_dir = static_cast<Direction>(rng.getInt(0, 8));
	switch ( _dir ) {
	case UP:
		nextY -= 1;
		break;
	case LEFT:
		nextX -= 1;
		break;
	case RIGHT:
		nextY += 1;
		break;
	case DOWN:
		nextX += 1;
		break;
	case TOP_LIFT:
		nextY -= 1;
		nextX -= 1;
		break;
	case TOP_RIGHT:
		nextY -= 1;
		nextX += 1;
		break;
	case DOWN_LIFT:
		nextY += 1;
		nextX -= 1;
		break;
	case DOWN_RIGHT:
		nextY += 1;
		nextX += 1;
		break;
	}

	if ( nextX < 0 || nextX >= GAME_WINDOW_WIDTH || nextY < 0 ||
	     nextY >= GAME_WINDOW_HEIGHT ) {
		switch ( _dir ) {
		case Direction::UP:
			_dir = Direction::DOWN;
			break;
		case Direction::DOWN:
			_dir = Direction::UP;
			break;
		case Direction::LEFT:
			_dir = Direction::RIGHT;
			break;
		case Direction::RIGHT:
			_dir = Direction::LEFT;
			break;
		case Direction::TOP_LIFT:
			_dir = Direction::DOWN_RIGHT;
			break;
		case Direction::TOP_RIGHT:
			_dir = Direction::DOWN_LIFT;
			break;
		case Direction::DOWN_LIFT:
			_dir = Direction::TOP_RIGHT;
			break;
		case Direction::DOWN_RIGHT:
			_dir = Direction::TOP_LIFT;
			break;
		}
	}

	_pos.x() = nextX;
	_pos.y() = nextY;
}

RPSType RPSGameObject::getType() const {
	return _type;
}

void RPSGameObject::setType(RPSType type) {
	if ( type == _type ) {
		return;
	}
	IconFactory factory = IconFactory();
	_icon = *factory.create_icon(type);
	_type = type;
}

void RPSGameObject::setDirection(Direction dir) {
	_dir = dir;
}
