#include "sidebar.h"
#include "element.h"
#include "sound.h"
#include "globals.h"

using namespace std::chrono_literals;

struct SpriteWhenClicked final {
    ElementId elem;
    std::chrono::milliseconds resetTime = 0ms;
};

struct AttachWhenClicked final {
    ElementId elem;
    ShowId itemId;
};

struct SoundWhenClicked final {
    ElementId elem;
    SoundId sound;
};

static SpriteWhenClicked clickImgs[]{{ElementId::binSideBar}, {ElementId::sinkSideBar}, {ElementId::fridge}};

static constexpr AttachWhenClicked attachElems[]{
    {ElementId::bowlsSideBar, ShowId::empty_bowl},     {ElementId::chopsticksSideBar, ShowId::chopsticks1},
    {ElementId::potSideBar, ShowId::empty_pot},        {ElementId::classicRamenSideBar, ShowId::classicRamen},
    {ElementId::sinkSideBar, ShowId::pot_water_added}, {ElementId::softdrink1, ShowId::softdrink_kola},
    {ElementId::softdrink2, ShowId::softdrink_funta},  {ElementId::softdrink3, ShowId::softdrink_peppy},
    {ElementId::softdrink4, ShowId::softdrink_spryte}};

static constexpr SoundWhenClicked soundElems[]{{ElementId::binSideBar, SoundId::bin_open},
                                               {ElementId::sinkSideBar, SoundId::running_water},
                                               {ElementId::fridge, SoundId::fridge}};

void SideBar::handleClick(ElementId elemId) noexcept {
    auto img = std::find_if(std::begin(clickImgs), std::end(clickImgs),
                            [elemId](const SpriteWhenClicked& e) { return e.elem == elemId; });
    if (img != std::end(clickImgs)) {
        getElement(elemId).src = SrcRatio{Sprite1x2::lower};
        img->resetTime         = m_tick + 500ms;
    }

    auto attach = std::find_if(std::begin(attachElems), std::end(attachElems),
                               [elemId](const AttachWhenClicked& e) { return e.elem == elemId; });
    if (attach != std::end(attachElems)) {
        attachToMouse(attach->elem, attach->itemId);
    }

    auto sd = std::find_if(std::begin(soundElems), std::end(soundElems),
                           [elemId](const SoundWhenClicked& e) { return e.elem == elemId; });
    if (sd != std::end(soundElems)) {
        m_mixer.play(sd->sound);
    }

    if (elemId == ElementId::binSideBar) {
        clearMouseItem();
    }

    if (elemId == ElementId::fridge) {
        offerSoftdrinks();
    }

    if (isSoftdrinkOption(elemId)) {
        dismissSoftdrinks();
    }
}

void SideBar::handleTick(std::chrono::milliseconds tick) noexcept {
    m_tick   = tick;
    auto img = std::find_if(std::begin(clickImgs), std::end(clickImgs), [tick](const SpriteWhenClicked& e) {
        return (e.resetTime != 0ms) && (tick >= e.resetTime);
    });

    if (img != std::end(clickImgs)) {
        getElement(img->elem).src = SrcRatio{Sprite1x2::upper};
        img->resetTime            = 0ms;
    }
}