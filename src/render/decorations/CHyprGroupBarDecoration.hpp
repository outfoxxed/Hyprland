#pragma once

#include "IHyprWindowDecoration.hpp"
#include <deque>
#include "../Texture.hpp"
#include <string>
#include <memory>

class CTitleTex {
  public:
    CTitleTex(PHLWINDOW pWindow, const Vector2D& bufferSize);
    ~CTitleTex();

    CTexture     tex;
    std::string  szContent;
    PHLWINDOWREF pWindowOwner;
};

void refreshGroupBarGradients();

class CHyprGroupBarDecoration : public IHyprWindowDecoration {
  public:
    CHyprGroupBarDecoration(PHLWINDOW);
    virtual ~CHyprGroupBarDecoration();

    virtual SDecorationPositioningInfo getPositioningInfo();

    virtual void                       onPositioningReply(const SDecorationPositioningReply& reply);

    virtual void                       draw(CMonitor*, float a);

    virtual eDecorationType            getDecorationType();

    virtual void                       updateWindow(PHLWINDOW);

    virtual void                       damageEntire();

    virtual bool                       onInputOnDeco(const eInputType, const Vector2D&, std::any = {});

    virtual eDecorationLayer           getDecorationLayer();

    virtual uint64_t                   getDecorationFlags();

    virtual std::string                getDisplayName();

  private:
    SWindowDecorationExtents m_seExtents;

    CBox                     m_bAssignedBox = {0};

    PHLWINDOWREF             m_pWindow;

    std::deque<PHLWINDOWREF> m_dwGroupMembers;

    float                    m_fBarWidth;

    CTitleTex*               textureFromTitle(const std::string&);
    void                     invalidateTextures();

    CBox                     assignedBoxGlobal();

    bool                     onBeginWindowDragOnDeco(const Vector2D&);
    bool                     onEndWindowDragOnDeco(const Vector2D&, PHLWINDOW);
    bool                     onMouseButtonOnDeco(const Vector2D&, wlr_pointer_button_event*);
    bool                     onScrollOnDeco(const Vector2D&, wlr_pointer_axis_event*);

    struct STitleTexs {
        // STitleTexs*                            overriden = nullptr; // TODO: make shit shared in-group to decrease VRAM usage.
        std::deque<std::unique_ptr<CTitleTex>> titleTexs;
    } m_sTitleTexs;
};
