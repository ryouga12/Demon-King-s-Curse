#pragma once
#include"../Scene/BaseScene.h"
#include "../dxlib_ext/dxlib_ext.h"
#include"../Map/Mapchip.h"


class MapScene : public BaseScene {
public:
	MapScene();

	void Update(float delta_time)override;
	void Draw()override;

	//csvのmapchipを格納する配列
	std::vector<std::vector<int>>world_map_csv;

	std::vector<std::vector<int>>world_continent_csv;
	
	std::list<Shared<MapChip*>>MapChips;

	std::list<Shared<MapChip*>>MapChip_continent;

private:
	tnl::Sequence<MapScene> sequence_ = tnl::Sequence<MapScene>(this, &MapScene::seqIdle);
	bool seqIdle(float delta_time);

	//mapchip関連
	std::string map_chip_ghdl_pass;
	//csvのdataのpass
	std::string map_chip_csv_pass;





};