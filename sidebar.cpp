#include "sidebar.h"
#include "element.h"
#include "sound.h"

using namespace std::chrono_literals;
void SideBar::handleClick(ElementId elemId) noexcept {
    if (!sinkClicked && elemId == ElementId::sinkSideBar) {
        auto sink = std::find_if(std::begin(m_elemsView), std::end(m_elemsView),
                                 [](const Element& e) { return e.elemId == ElementId::sinkSideBar; });
        if (sink != std::end(m_elemsView)) {
            sink->imgId = ImageId::sink_running_water;
            sink->ratio = 1.5f;
        }
        sinkClicked = true;
        m_mixer.play(SoundId::running_water);
    }

    if (!binClicked && elemId == ElementId::binSideBar) {
        auto bin = std::find_if(std::begin(m_elemsView), std::end(m_elemsView),
                                [](const Element& e) { return e.elemId == ElementId::binSideBar; });
        if (bin != std::end(m_elemsView)) {
            bin->imgId = ImageId::bin_open;
            bin->ratio = 1.5f;
        }
        binClicked = true;
        m_mixer.play(SoundId::bin_open);
    }
}

void SideBar::handleTick(std::chrono::milliseconds tick) noexcept {
    using namespace std::chrono_literals;
    if (sinkClicked) {
        if ((tick - sinkStart) > 500ms) {
            auto itr = std::find_if(std::begin(m_elemsView), std::end(m_elemsView),
                                    [](const Element& e) { return e.elemId == ElementId::sinkSideBar; });
            if (itr != std::end(m_elemsView)) {
                itr->imgId = ImageId::sink;
                itr->ratio = 1.f;
            }
            sinkClicked = false;
        }
    } else {
        sinkStart = tick;
    }

    if (binClicked) {
        if ((tick - binStart) > 500ms) {
            auto itr = std::find_if(std::begin(m_elemsView), std::end(m_elemsView),
                                    [](const Element& e) { return e.elemId == ElementId::binSideBar; });
            if (itr != std::end(m_elemsView)) {
                itr->imgId = ImageId::bin;
                itr->ratio = 1.f;
            }
            binClicked = false;
        }
    } else {
        binStart = tick;
    }
}

void SideBar::handleCycleStart() noexcept {}
void SideBar::handleCycleEnd() noexcept {}