#pragma once

#include "include/cells.hpp"

#include <Geode/ui/Popup.hpp>
#include "blur/CCBlurLayer.hpp"

// interface code in menu
enum class Page {
    Terminal, Init, Item, Setup, Color, Options, Info, Warn
};

// fubao is like a clever neko witch
// miss her super much
class ChromaLayer : public Popup<>, public ColorPickerDelegate {
protected:
    /********** VARIENT CENTRAL ***********/

    // interface status chain
    // @note for initialize the first node is Init, when you're gonna quit the menu we temply add a Terminal node
    // @note if warn page is triggered, warn page will be added firstly
    std::vector<Page> pages;

    // dual player 1/2
    bool ptwo;

    // the identifier of the current modifying icon/effect for setup menu
    // @note easy mode : common = 0
    // @note adv mode : icons = 1-9
    // @note Effects (11~15) : trail, wave trail, dash fire, teleport line, ufo shell...
    int id;

    // current gamemode in setup page
    // @note icon-jetpack = 0-9
    Gamemode gamemode;

    // record adv mode gamemode when switching to ez mode
    Gamemode history;

    // current item channel in setup page
    // @note main/second/glow/white
    Channel channel = Channel::Main;

    // current editing color tag in case color page dosen't know what he's working on
    int colorTag = 0;

    // phase for schedule update
    float phase = 0;
    // percentage simulator
    float percentage = 0;

    // current config data
    ChromaSetup currentSetup = DEFAULT_SETUP;

    // current color
    // @note varient inside color page
    ccColor3B oriColor;
    // original color
    // @note fixed inside color page
    ccColor3B crtColor;

    // setup scroller
    SetupItemCell* m_currentItem = nullptr;

    std::pair<bool, ccColor3B> clipColor;
    std::pair<bool, ChromaSetup> clipSetup;

    /********** UI THINGS ***********/

    // background
    CCLayerColor* m_bg = nullptr;
    // blur layer
    CCBlurLayer* m_blur = nullptr;

    bool on_slider = false;
    // all cell nodes to switch theme (except option cells)
    CCArrayExt<BaseCell*> m_cells;

    // warning page
    WarnCell* m_warnPage;

    // exit button
    CCMenuItemSpriteExtra* m_exitBtn;
    // info button
    CCMenuItemSpriteExtra* m_infoBtn;
    // apply button
    CCMenuItemSpriteExtra* m_applyBtn;
    // options button
    CCMenuItemSpriteExtra* m_optionsBtn;
    // mode button
    CCMenuItemToggler* m_modeBtn;
    // copy button
    CCMenuItemSpriteExtra* m_copyBtn;
    // paste button
    CCMenuItemSpriteExtra* m_pasteBtn;

    // title
    CCLabelBMFont* m_titleLabel;
    // player switch
    CCMenuItemToggler* m_playerItemBtn;
    // full icons
    ItemCell* m_advBundleCell;
    // single icon
    ItemCell* m_ezyBundleCell;
    // effect
    ItemCell* m_effBundleCell;

    // setup player switch
    CCMenuItemToggler* m_playerSetupBtn;
    // setup item label
    CCLabelBMFont* m_itemSetupLabel;
    // setup channel label
    CCLabelBMFont* m_chnlSetupLabel;
    // setup adv items scroller
    ScrollLayerPlus* m_setupAdvScroller;
    // setup easy items scroller
    ScrollLayerPlus* m_setupEasyScroller;
    // main setup workspace
    SetupOptionCell* m_workspace;
    // temp setup space
    SetupOptionCell* m_waitspace;    
    // setup channel switch left
    CCMenuItemSpriteExtra* m_leftArrowSetupBtn;
    // setup channel switch right
    CCMenuItemSpriteExtra* m_rightArrowSetupBtn;

    // display what id and channel he is working on
    CCLabelBMFont* m_colorTitle;
    // display what color he is now configuring
    CCLabelBMFont* m_colorItem;
    // original color displayer
    CCMenuItemSpriteExtra* m_oriColorDisplay;
    // current color displayer
    CCMenuItemSpriteExtra* m_crtColorDisplay;
    // arrow
    CCSprite* m_mysteriousArrow;
    // picker
    CCControlColourPicker* m_picker;
    // R val
    ColorValueCell* m_redCell;
    // G val
    ColorValueCell* m_greenCell;
    // B val
    ColorValueCell* m_blueCell;
    // HEX val
    ColorHexCell* m_hexCell;

    // copy ori
    CCMenuItemSpriteExtra* m_copyOriBtn;
    // resc ori
    CCMenuItemSpriteExtra* m_rescOriBtn;
    // copy crt
    CCMenuItemSpriteExtra* m_copyCrtBtn;
    // resc paste
    CCMenuItemSpriteExtra* m_pasteCrtBtn;
    // option scroller
    ScrollLayerPlus* m_optionScroller;

    /********** LISTENERS ***********/

    EventListener<EventFilter<SignalEvent<bool>>> boolListener
        = EventListener<EventFilter<SignalEvent<bool>>>(
            [this](SignalEvent<bool>* event) -> ListenerResult { return this->handleBoolSignal(event); });

    EventListener<EventFilter<SignalEvent<int>>> intListener
        = EventListener<EventFilter<SignalEvent<int>>>(
            [this](SignalEvent<int>* event) -> ListenerResult { return this->handleIntSignal(event); });

    EventListener<EventFilter<SignalEvent<float>>> floatListener
        = EventListener<EventFilter<SignalEvent<float>>>(
            [this](SignalEvent<float>* event) -> ListenerResult { return this->handleFloatSignal(event); });

    EventListener<EventFilter<SignalEvent<ccColor3B>>> colorListener
        = EventListener<EventFilter<SignalEvent<ccColor3B>>>(
            [this] (SignalEvent<ccColor3B>* event) -> ListenerResult { return this->handleColorSignal(event); });

    /*********** INITIAL SETUP ***********/

    // makup initial UI
    bool setup() override;

    /*********** UTILITY ***********/

    // override update
    void update(float xdt) override;

    // get color target
    // @return point to the color button who calls color page
    CCMenuItemSpriteExtra* getColorTarget();

    //refresh some chroma preview status when setup changed
    void dumpConfig();

    // save config -> switch current ID and refresh setup page
    // @param id new target id he will switch to.
    // @return true if the value is really changed
    bool switchCurrentItem(int id);

    // ColorPickerDelegate function override
    // @param color new color from the picker
    void colorValueChanged(ccColor3B color) override;

    /*********** TRANSITION ***********/

    // cover speed member value and change menu chroma speed
    // @param t time interval
    void updateSpeedValue(float t);

    // switch theme color between dark and white
    void switchTheme();

    // fade in or out main menu buttons in the four corners
    //void fadeMainMenuButtons();

    // refresh color page status
    // @param type 0->init 1->rgb 2->hex 3->circle 4->restore
    void refreshColorPage(int type);

    void transistColorBtn(bool isCrt, bool display);

    // run main ui animation
    void fadeMainMenu();

    // run warning page animation
    void fadeWarnPage();

    // run item select page
    void fadeItemPage();

    // run setup ui animation
    void fadeSetupPage();

    // run pickcolor ui animation
    void fadeColorPage();

    // run options ui animation
    void fadeOptionsPage();

    // run info ui animation
    void fadeInfoPage();

    /*********** EVENT HANDLERS ***********/

    // handle bool signal
    ListenerResult handleBoolSignal(SignalEvent<bool>* event);

    // handle int signal
    ListenerResult handleIntSignal(SignalEvent<int>* event);

    // handle float signal
    ListenerResult handleFloatSignal(SignalEvent<float>* event);

    // handle color signal
    ListenerResult handleColorSignal(SignalEvent<ccColor3B>* event);

    /*************** CALLBACK ***************/

    // switch player
    // @param sender m_playerBtn1->tag = 4 m_playerBtn2->tag = 2
    void onSwitchPlayer(CCObject* sender);

    // on switch easy/advanced mode
    // @param sender the easy adv button
    void onSwitchEasyAdv(CCObject* sender);

    // flip channel page
    // @param sender m_leftArrowSetupBtn->tag = 4 m_rightArrowSetupBtn->tag = 2
    void onSwitchChannelPage(CCObject* sender);

    // click the options button
    // @param sender the options button
    void onOptionsPage(CCObject* sender);

    // launch info page
    // @param sender the options button
    void onInfoPage(CCObject* sender);

    // clicked an info button
    // @param sender the options button
    void onInfoButtons(CCObject* sender);

    // expand or collapse sub buttons
    void onColorDisplayBtn(CCObject* sender);

    // copy setup / color
    // @param sender copy button's tags are important signal
    // @note copy button 1->ori 3->crt 5->setup
    void onCopy(CCObject* sender);

    // paste setup / color
    // @param sender paste button's tags are important signal
    // @note paste button 4->crt 6->setup
    void onPaste(CCObject* sender);

    // resc color
    // @param sender resc button
    // @note resc button 2->ori
    void onResc(CCObject* sender);

    // apply setup / color
    // @param sender apply button
    void onApply(CCObject* sender);

    // override onClose feedback
    // @param sender actually not important
    void onClose(CCObject*) override;
public:
    // hey anyone will use it?
    const std::string CLASS_NAME = "ChromaLayer";

    // process some init animation
    void show() override;

    // not knowing why android directly leave mod menu
    void keyBackClicked() override {
        this->onClose(nullptr);
    }
    // constructor
    static ChromaLayer* create() {
        auto layer = new ChromaLayer();

        if (layer && layer->initAnchored(420.f, 280.f)) {
            layer->autorelease();
            return layer;
        };
        CC_SAFE_DELETE(layer);
        return nullptr;
    }
};