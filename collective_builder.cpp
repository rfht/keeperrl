#include "stdafx.h"
#include "collective_builder.h"
#include "collective.h"
#include "location.h"
#include "creature.h"
#include "creature_name.h"
#include "collective_name.h"
#include "creature_attributes.h"
#include "collective_config.h"
#include "tribe.h"
#include "collective_control.h"
#include "immigration.h"

CollectiveBuilder::CollectiveBuilder(const CollectiveConfig& cfg, TribeId t)
    : config(cfg), tribe(t) {
}

CollectiveBuilder& CollectiveBuilder::setLevel(Level* l) {
  level = l;
  return *this;
}

CollectiveBuilder& CollectiveBuilder::setLocationName(const string& n) {
  locationName = n;
  return *this;
}

CollectiveBuilder& CollectiveBuilder::setRaceName(const string& n) {
  raceName = n;
  return *this;
}

CollectiveBuilder& CollectiveBuilder::addCreature(WCreature c) {
  if (!c->getAttributes().isInnocent() && (!creatures.empty() || config->isLeaderFighter()))
    creatures.push_back({c, {MinionTrait::FIGHTER}});
  else
    creatures.push_back({c, {}});
  return *this;
}

CollectiveBuilder& CollectiveBuilder::addSquares(const vector<Vec2>& v) {
  append(squares, v);
  return *this;
}

CollectiveBuilder& CollectiveBuilder::addSquares(const vector<Position>& v) {
  for (auto& pos : v)
    squares.push_back(pos.getCoord());
  return *this;
}

PCollective CollectiveBuilder::build() {
  CHECK(!creatures.empty());
  CHECK(level);
  auto c = makeOwner<Collective>(level, *tribe, CollectiveName(raceName, locationName, creatures[0].creature));
  Immigration im(c.get());
  c->init(std::move(*config), std::move(im));
  c->setControl(CollectiveControl::idle(c.get()));
  for (auto& elem : creatures)
    c->addCreature(elem.creature, elem.traits);
  for (Vec2 v : squares) {
    Position pos(v, level);
    c->addKnownTile(pos);
    //if (c->canClaimSquare(pos))
      c->claimSquare(pos);
  }
  return c;
}

bool CollectiveBuilder::hasCreatures() const {
  return !creatures.empty();
}
