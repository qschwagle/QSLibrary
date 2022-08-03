//
// Created by Quinton Schwagle on 7/30/22.
//

#ifndef DRAWING_MY_APP_DELEGATE_H
#define DRAWING_MY_APP_DELEGATE_H

#include "Foundation/Foundation.hpp"
#include "Metal/Metal.hpp"
#include "MetalKit/MetalKit.h"
#include "QuartzCore/QuartzCore.hpp"
#include "AppKit/AppKit.hpp"

class MyAppDelegate : public NS::ApplicationDelegate
{
public:
    virtual ~MyAppDelegate();

    NS::Menu* CreateMenuBar();

    virtual void applicationWillFinishLaunching(NS::Notification* notification) override;
    virtual void applicationDidFinishLaunching(NS::Notification* notifcation) override;
    virtual bool applicationShouldTerminateAfterLastWindowClosed(NS::Application* sender) override;

private:
    NS::Window* mWindow;
    MTK::View* mMtkView;
    MTL::Device* mDevice;
};


#endif //DRAWING_MY_APP_DELEGATE_H
