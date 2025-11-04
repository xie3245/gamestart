#include "sidebar.h"
#include "element.h"
#include "sound.h"
#include "globals.h"

using namespace std::chrono_literals;

struct ClickEvents final {
    ElementId toClick;
    ElementId attachRequireOnMouse = ElementId::undefined;
    ElementId attachForbidOnMouse  = ElementId::undefined;
};

struct ImageWhenClicked final {
    ElementId elem;
    ShowId imgOrig;
    ShowId imgClicked;
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

static ImageWhenClicked clickImgs[]{{ElementId::binSideBar, ShowId::bin, ShowId::bin_open},
                                    {ElementId::sinkSideBar, ShowId::sink, ShowId::sink_running_water}};

static constexpr AttachWhenClicked attachElems[]{{ElementId::bowlsSideBar, ShowId::empty_bowl},
                                                 {ElementId::chopsticksSideBar, ShowId::chopsticks1},
                                                 {ElementId::potSideBar, ShowId::empty_pot},
                                                 {ElementId::ramenSideBar, ShowId::ramenPkg},
                                                 {ElementId::sinkSideBar, ShowId::pot_water_added}};

static constexpr SoundWhenClicked soundElems[]{{ElementId::binSideBar, SoundId::bin_open},
                                               {ElementId::sinkSideBar, SoundId::running_water}};

void SideBar::handleClick(ElementId elemId) noexcept {
    auto img = std::find_if(std::begin(clickImgs), std::end(clickImgs),
                            [elemId](const ImageWhenClicked& e) { return e.elem == elemId; });
    if (img != std::end(clickImgs)) {
        getElement(elemId).showId = img->imgClicked;
        img->resetTime            = m_tick + 500ms;
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
}

void SideBar::handleTick(std::chrono::milliseconds tick) noexcept {
    m_tick   = tick;
    auto img = std::find_if(std::begin(clickImgs), std::end(clickImgs), [tick](const ImageWhenClicked& e) {
        return (e.resetTime != 0ms) && (tick >= e.resetTime);
    });

    if (img != std::end(clickImgs)) {
        getElement(img->elem).showId = img->imgOrig;
        img->resetTime               = 0ms;
    }
}