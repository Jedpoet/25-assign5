#include "RPSGameObject.h"
#include "environment.h"
#include "iconFactory.h"

bool RPSGameObject::intersect(ICollider *other) {
	auto *otherObj = dynamic_cast<RPSGameObject *>(other);
	if ( !otherObj ) {
		return false;
	}

	int dx = std::abs(_pos.x() - otherObj->_pos.x());
	int dy = std::abs(_pos.y() - otherObj->_pos.y());

	return dx <= 1 && dy <= 1; // 2x2 區域（含自身與相鄰）
}

int RPSGameObject::onCollision(ICollider *other) {
	auto *otherObj = dynamic_cast<RPSGameObject *>(other);
	if ( !otherObj )
		return 0;

	RPSType self = this->getType();
	RPSType enemy = otherObj->getType();

	int ans = 0;

	if ( self != enemy ) {
		// 被剋就轉型
		if ( (self == RPSType::ROCK && enemy == RPSType::PAPER) ||
		     (self == RPSType::PAPER && enemy == RPSType::SCISSORS) ||
		     (self == RPSType::SCISSORS && enemy == RPSType::ROCK) ) {
			this->setType(enemy);
		}

		switch ( enemy ) {
		case ROCK:
			ans = 1;
			if ( is_player ) {
				ans = 4;
			}
			break;
		case SCISSORS:
			ans = 2;
			break;
		case PAPER:
			ans = 3;
			break;
		}
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
	default:
		break;
	}

	return ans;
}

void RPSGameObject::update() {
	int nextX = _pos.x();
	int nextY = _pos.y();

tryto:
	switch ( _dir ) {
	case UP:
		nextY -= 1;
		break;
	case LEFT:
		nextX -= 1;
		break;
	case RIGHT:
		nextX += 1;
		break;
	case DOWN:
		nextY += 1;
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
	default:
		break;
	}

	if ( nextX < 0 || nextX >= GAME_WINDOW_WIDTH || nextY < 0 ||
	     nextY >= GAME_WINDOW_HEIGHT ) {
		onCollision(this);
		goto tryto;
	}
	_pos.x() = nextX;
	_pos.y() = nextY;

	_dir = static_cast<Direction>(rng.getInt(0, 8));
}

RPSType RPSGameObject::getType() const {
	return _type;
}

void RPSGameObject::setType(RPSType type) {
	if ( type == _type ) {
		return;
	}
	IconFactory factory = IconFactory();
	_icon = *factory.create_icon(this);
	_type = type;
}

void RPSGameObject::setDirection(Direction dir) {
	_dir = dir;
}

void RPSGameObject::playerSwitch() {
	is_player = !is_player;
}

bool RPSGameObject::isPlayer() const {
	return is_player;
}
