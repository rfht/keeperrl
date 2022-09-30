#include "util.h"
#include "view.h"

namespace CampaignMenuElems {
  EMPTY_STRUCT(RetiredDungeons);
  EMPTY_STRUCT(Settings);
  EMPTY_STRUCT(ChangeMode);
  EMPTY_STRUCT(Help);
  struct Biome {
    int value;
    COMPARE_ALL(value);
  };
  EMPTY_STRUCT(Confirm);
  EMPTY_STRUCT(RollMap);
  EMPTY_STRUCT(Back);
  using CampaignMenuIndexVariant = variant<RetiredDungeons, Settings, ChangeMode, Help, Biome, Confirm,
      RollMap, Back>;
}

struct CampaignMenuIndex : public CampaignMenuElems::CampaignMenuIndexVariant {
  template <typename T>
  void assign(T elem) {
    *((CampaignMenuElems::CampaignMenuIndexVariant*)this) = std::move(elem);
  }
  void left(const View::CampaignOptions&);
  void right(const View::CampaignOptions&);
  void up(const View::CampaignOptions&);
  void down(const View::CampaignOptions&);
};