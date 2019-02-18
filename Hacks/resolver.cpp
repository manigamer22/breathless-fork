#include "main.h"

// hi jason

/*
 
 ...
 ;::::;
 ;::::; :;
 ;:::::'   :;
 ;:::::;     ;.
 ,:::::'       ;           OOO
 ::::::;       ;          OOOOO
 ;:::::;       ;         OOOOOOOO
 ,;::::::;     ;'         / OOOOOOO
 ;:::::::::`. ,,,;.        /  / DOOOOOO
 .';:::::::::::::::::;,     /  /     DOOOO
 ,::::::;::::::;;;;::::;,   /  /        DOOO
 ;`::::::`'::::::;;;::::: ,#/  /          DOOO
 :`:::::::`;::::::;;::: ;::#  /            DOOO
 ::`:::::::`;:::::::: ;::::# /              DOO
 `:`:::::::`;:::::: ;::::::#/               DOO
 :::`:::::::`;; ;:::::::::##                OO
 ::::`:::::::`;::::::::;:::#                OO
 `:::::`::::::::::::;'`:;::#                O
 `:::::`::::::::;' /  / `:#
 ::::::`:::::;'  /  /   `#
 
 its supposed to be a grim reaper
 
 */

RecvVarProxyFn OldProxy_Y; //OldProxy_X;

// Pitch Resolver
/*
 float AAA_Pitch(C_BaseEntity* entity){
 int index = entity->GetIndex();
 float angle = gCorrections[index].x;
 
 angle = 89;
 }
 */

float get_average_lby_standing_update_delta(C_BaseEntity* entity) {
    static float last_update_time[64];
    static float second_laste_update_time[64];
    static float oldlowerbody[64];
    int index = entity->GetIndex();
    float angle = gCorrections[index].y;
    float lby = static_cast<int>(fabs(angle - entity->GetLowerBodyYawTarget()));
    
    if (lby != oldlowerbody[entity->GetIndex()]) {
        second_laste_update_time[entity->GetIndex()] = last_update_time[entity->GetIndex()];
        last_update_time[entity->GetIndex()] = pGlobals->curtime;
        oldlowerbody[entity->GetIndex()] = lby;
    }
    
    return last_update_time[entity->GetIndex()] - second_laste_update_time[entity->GetIndex()];
}

bool lby_keeps_updating() {
    return get_average_lby_standing_update_delta;
}


float AAA_Yaw(C_BaseEntity* entity)
{
    int index = entity->GetIndex();
    float angle = gCorrections[index].y;
    
    bool LBYbreak;
    for (int i = 0; i < 13; i++)
    {
        entity->GetAnimTime();
    }
    
    bool IsMovingOnInAir = {
        //Check if player has a velocity greater than 0 (moving) and if they are onground.
        !(entity->GetFlags() & FL_ONGROUND)
    };
    
    bool OnGround = (entity->GetFlags() & FL_ONGROUND);
    
    bool MovingOnGround = {
        //Check if player has a velocity greater than 0 (moving) and if they are onground.
        entity->GetVelocity().Length2D() > 45.f && entity->GetFlags() & FL_ONGROUND
    };
    
    // Fake Walk dectection
    bool maybeFakeWalking;
    MovingOnGround && entity->GetVelocity().Length2D() < 36.0f;
    
    bool HasFakeHead = {
        //lby should update if distance from lby to eye angles exceeds 35 degrees
        abs(entity->GetEyeAngles()->y - entity->GetLowerBodyYawTarget()) > 35
    };
    
    
    bool Lbywithin35 = {
        //lby should update if distance from lby to eye angles less than 35 degrees=
        abs(entity->GetEyeAngles()->y - entity->GetLowerBodyYawTarget()) < 35
    };
    
    int shotmissed = 0;
    bool shots = 1;
    bool bLowerBodyUpdated;
    
    if (vars.aimbot.yresolve == 1)
    { // rev(testing)
        
#define RandomFloat(min, max) (rand() % (max - min + 1) + min)
        
        auto index = entity->GetIndex();
        
        
        static float LatestLowerBodyYaw[65];
        static float LatestLowerBodyYawUpdateTime[65];
        static float lbyproxytime;
        static float enemyLBYTimer[65];
        static float oldlowerbodyyawTest;
        
        
        static int missedLogHits[65];
        static float saveLastHeadshotFloat[65];
        static float saveLastBaimFloat[65];
        static float saveLastBaim30Float[65];
        static float enemysLastProxyTimer[65];
        static bool shotFakeHeadOnce[65];
        static int fakeshotMissedLast[65];
        static int ResolverStage[65];
        static int deltas[65];
        
        
        float deltadif = abs(angle - entity->GetLowerBodyYawTarget());
        lbyproxytime = enemysLastProxyTimer[entity->GetIndex()] + 0.2f;
        
        
        
        auto new_yaw = angle;
        int vel = entity->GetVelocity().Length2D();
        float cur = pGlobals->curtime;
        float CurrentLowerbody = entity->GetLowerBodyYawTarget();
        bool is_fakewalk = entity->GetVelocity().Length2D() > 0 && entity->GetVelocity().Length2D() < 50;
        bool is_moving = entity->GetVelocity().Length2D() >= 50;
        bool is_standing = entity->GetVelocity().Length2D() == 0;
        bool is_onground = entity->GetFlags() & FL_ONGROUND;
        bool is_nospread = entity->GetVelocity().Length2D() > 250;
        
        
        if (is_onground)
        {
            
            
            
            if (entity->GetLowerBodyYawTarget() != LatestLowerBodyYaw[index] || (is_moving && !is_fakewalk && !is_standing))
            {
                LatestLowerBodyYaw[index] = entity->GetLowerBodyYawTarget();
                ResolverStage[index] = 1;
                LatestLowerBodyYawUpdateTime[index] = pGlobals->curtime;
                
                return (entity->GetLowerBodyYawTarget());
                
            }
            else
            {
                if (is_fakewalk)
                {
                    
                    if (deltadif && (cur, 10))
                    {
                        new_yaw = entity->GetLowerBodyYawTarget() - 40;
                        //Delta Changes
                        ResolverStage[index] = 2;
                    }
                    else if (entity->GetLowerBodyYawTarget() && (cur, 10))
                    {
                        new_yaw = entity->GetLowerBodyYawTarget() + 40;
                        //Lowerbody Changes
                        ResolverStage[index] = 3;
                    }
                    else {
                        new_yaw = angle + 180;
                        ResolverStage[index] = 21;
                    }
                    
                    
                }
                if (is_standing)
                {
                    
                    if (missedLogHits[index] <= 4) {
                        
                        switch (shots % 5)//5
                        {
                           case 1:
                                new_yaw = oldlowerbodyyawTest - 45;
                                break;
                            case 2:
                                new_yaw = CurrentLowerbody + 45;
                                break;
                            case 3:
                                new_yaw = oldlowerbodyyawTest;
                                break;
                            case 4:
                                new_yaw = CurrentLowerbody + 90;
                                break;
                            case 5:
                                new_yaw = CurrentLowerbody - 90;
                                break;
                        }
                        
                    }
                    
                    // Predict it only once a Round
                    if (shotFakeHeadOnce[index] == false) {
                        
                        if (((pGlobals->curtime - LatestLowerBodyYawUpdateTime[index]) >= 1.1))
                        {
                            new_yaw = CurrentLowerbody + RandomFloat(-35, 35);
                            ResolverStage[index] = 4;
                            shotFakeHeadOnce[index] = true;
                        }
                        
                    }
                    else
                    {
                        if (std::abs(LatestLowerBodyYaw[index] - CurrentLowerbody) <= 10)
                        {
                            int random = rand() % 10;
                            if (random < 6)
                            {
                                new_yaw = CurrentLowerbody + RandomFloat(-10, 10);
                                ResolverStage[index] = 1;
                            }
                            else
                            {
                                new_yaw = CurrentLowerbody;
                                ResolverStage[index] = 6;
                            }
                        }
                        else
                        {
                            if (deltadif && (cur, 10))
                            {
                                new_yaw = deltas[entity->GetIndex()];
                                ResolverStage[index] = 2;
                            }
                            else if (entity->GetLowerBodyYawTarget() && (cur, 10))
                            {
                                new_yaw = entity->GetLowerBodyYawTarget() - deltadif;
                                ResolverStage[index] = 3;
                            }
                        }
                    }
                    
                }
            }
            
            
            if (missedLogHits[index] == 3 || missedLogHits[index] == 4) {
                // Try Database Log Hits
                ResolverStage[index] = 9;
                
                if (saveLastHeadshotFloat[index] != 0) {
                    new_yaw = saveLastHeadshotFloat[index];
                    
                }
                else if (saveLastBaimFloat[index] != 0) {
                    new_yaw = saveLastBaimFloat[index];
                    
                }
                else if (saveLastBaim30Float[index] != 0) {
                    new_yaw = saveLastBaim30Float[index];
                    
                }
                else {
                    
                    new_yaw = deltadif;
                    
                }
                
            }
            else if (missedLogHits[index] == 5 || missedLogHits[index] == 6 || missedLogHits[index] == 7) {
                
                ResolverStage[index] = 11;
                
                if (missedLogHits[index] == 5) {
                    new_yaw = deltadif - entity->GetLowerBodyYawTarget();
                }
                
                if (missedLogHits[index] == 6 || missedLogHits[index] == 7) {
                    if (lbyproxytime != enemyLBYTimer[entity->GetIndex()] && abs(lbyproxytime - enemyLBYTimer[entity->GetIndex()]) > 0.8f) {
                        enemyLBYTimer[entity->GetIndex()] = lbyproxytime;
                        new_yaw = entity->GetLowerBodyYawTarget();
                        oldlowerbodyyawTest = entity->GetLowerBodyYawTarget();
                        
                    }
                    else {
                        
                        new_yaw = oldlowerbodyyawTest + deltadif;
                    }
                }
                
            }
            else if (missedLogHits[index] == 8) {
                // Try Database Log Hits
                ResolverStage[index] = 9;
                
                if (saveLastHeadshotFloat[index] != 0) {
                    
                    new_yaw = saveLastHeadshotFloat[index];
                    
                }
                else if (saveLastBaimFloat[index] != 0) {
                    
                    new_yaw = saveLastBaimFloat[index];
                    
                }
                else if (saveLastBaim30Float[index] != 0) {
                    
                    new_yaw = saveLastBaim30Float[index];
                    
                }
                else {
                    new_yaw = abs(entity->GetLowerBodyYawTarget() - angle);
                }
                
            }
            
            
            
            if (fakeshotMissedLast[index] <= 3) {
                
                if (abs(entity->GetLowerBodyYawTarget() - angle) > 35) {
                    // Enemy is using FakeAngle
                    new_yaw = angle - abs(entity->GetLowerBodyYawTarget() - angle);
                    ResolverStage[index] = 13;
                    fakeshotMissedLast[index] = missedLogHits[index];
                }
            }
            
            
        }
        else
        {
            if (is_nospread)
            {
                
                if (missedLogHits[index] <= 10) {
                    
                    switch (shots % 5)
                    {
                        case 1:
                            new_yaw = oldlowerbodyyawTest - 45;
                            break;
                        case 2:
                            new_yaw = CurrentLowerbody + 45;
                            break;
                        case 3:
                            new_yaw = oldlowerbodyyawTest;
                            break;
                        case 4:
                            new_yaw = CurrentLowerbody + 90;
                            break;
                        case 5:
                            new_yaw = CurrentLowerbody - 90;
                            break;
                    }
                    
                }
                else {
                    
                    new_yaw = RandomFloat(-35, 35);
                    
                }
                
            }
            else
            {
                new_yaw = entity->GetLowerBodyYawTarget();
                ResolverStage[index] = 7;
                
            }
            
            if(IsMovingOnInAir)
            {
                angle = entity->GetLowerBodyYawTarget();
            }
            
        }
        
        
        new_yaw = (new_yaw);
        return new_yaw;
    }

    if(vars.aimbot.yresolve == 2){//lby(same as rev pre much)
        
        #define RandomFloat(min, max) (rand() % (max - min + 1) + min)
        
        auto index = entity->GetIndex();
        
        
        static float LatestLowerBodyYaw[65];
        static float LatestLowerBodyYawUpdateTime[65];
        static float lbyproxytime;
        static float enemyLBYTimer[65];
        static float oldlowerbodyyawTest;
        
        
        static int missedLogHits[65];
        static float saveLastHeadshotFloat[65];
        static float saveLastBaimFloat[65];
        static float saveLastBaim30Float[65];
        static float enemysLastProxyTimer[65];
        static bool shotFakeHeadOnce[65];
        static int fakeshotMissedLast[65];
        static int ResolverStage[65];
        static int deltas[65];
        
        
        float deltadif = abs(angle - entity->GetLowerBodyYawTarget());
        lbyproxytime = enemysLastProxyTimer[entity->GetIndex()] + 0.2f;
        
        
        
        auto new_yaw = angle;
        int vel = entity->GetVelocity().Length2D();
        float cur = pGlobals->curtime;
        float CurrentLowerbody = entity->GetLowerBodyYawTarget();
        bool is_fakewalk = entity->GetVelocity().Length2D() > 0 && entity->GetVelocity().Length2D() < 50;
        bool is_moving = entity->GetVelocity().Length2D() >= 50;
        bool is_standing = entity->GetVelocity().Length2D() == 0;
        bool is_onground = entity->GetFlags() & FL_ONGROUND;
        bool is_nospread = entity->GetVelocity().Length2D() > 250;
        
        
        if (is_onground)
        {
            
            
            
            if (entity->GetLowerBodyYawTarget() != LatestLowerBodyYaw[index] || (is_moving && !is_fakewalk && !is_standing))
            {
                LatestLowerBodyYaw[index] = entity->GetLowerBodyYawTarget();
                ResolverStage[index] = 1;
                LatestLowerBodyYawUpdateTime[index] = pGlobals->curtime;
                
                return (entity->GetLowerBodyYawTarget());
                
            }
            else
            {
                if (is_fakewalk)
                {
                    
                    if (deltadif && (cur, 10))
                    {
                        new_yaw = entity->GetLowerBodyYawTarget();
                        //Delta Changes
                        ResolverStage[index] = 2;
                    }
                    else if (entity->GetLowerBodyYawTarget() && (cur, 10))
                    {
                        new_yaw = entity->GetLowerBodyYawTarget();
                        //Lowerbody Changes
                        ResolverStage[index] = 3;
                    }
                    else {
                        new_yaw = angle + 180;
                        ResolverStage[index] = 21;
                    }
                    
                    
                }
                if (is_standing)
                {
                    // Predict it only once a Round
                    if (shotFakeHeadOnce[index] == false) {
                        
                        if (((pGlobals->curtime - LatestLowerBodyYawUpdateTime[index]) >= 1.1))
                        {
                            new_yaw = CurrentLowerbody + 180;
                            ResolverStage[index] = 4;
                            shotFakeHeadOnce[index] = true;
                        }
                        
                    }
                    else
                    {
                        if (std::abs(LatestLowerBodyYaw[index] - CurrentLowerbody) <= 10)
                        {
                            int random = rand() % 10;
                            if (random < 6)
                            {
                                new_yaw = CurrentLowerbody + RandomFloat(-10, 10);
                                ResolverStage[index] = 1;
                            }
                            else
                            {
                                new_yaw = CurrentLowerbody;
                                ResolverStage[index] = 6;
                            }
                        }
                        else
                        {
                            if (deltadif && (cur, 10))
                            {
                                new_yaw = deltas[entity->GetIndex()];
                                ResolverStage[index] = 2;
                            }
                            else if (entity->GetLowerBodyYawTarget() && (cur, 10))
                            {
                                new_yaw = entity->GetLowerBodyYawTarget();
                                ResolverStage[index] = 3;
                            }
                        }
                    }
                    
                }
            }
            
            
            if (missedLogHits[index] == 3 || missedLogHits[index] == 4) {
                // Try Database Log Hits
                ResolverStage[index] = 9;
                
                if (saveLastHeadshotFloat[index] != 0) {
                    new_yaw = saveLastHeadshotFloat[index];
                    
                }
                else if (saveLastBaimFloat[index] != 0) {
                    new_yaw = saveLastBaimFloat[index];
                    
                }
                else if (saveLastBaim30Float[index] != 0) {
                    new_yaw = saveLastBaim30Float[index];
                    
                }
                else {
                    
                    new_yaw = deltadif;
                    
                }
                
            }
            else if (missedLogHits[index] == 5 || missedLogHits[index] == 6 || missedLogHits[index] == 7) {
                
                ResolverStage[index] = 11;
                
                if (missedLogHits[index] == 5) {
                    new_yaw = deltadif - entity->GetLowerBodyYawTarget();
                }
                
                if (missedLogHits[index] == 6 || missedLogHits[index] == 7) {
                    if (lbyproxytime != enemyLBYTimer[entity->GetIndex()] && abs(lbyproxytime - enemyLBYTimer[entity->GetIndex()]) > 0.8f) {
                        enemyLBYTimer[entity->GetIndex()] = lbyproxytime;
                        new_yaw = entity->GetLowerBodyYawTarget();
                        oldlowerbodyyawTest = entity->GetLowerBodyYawTarget();
                        
                    }
                    else {
                        
                        new_yaw = oldlowerbodyyawTest + deltadif;
                    }
                }
                
            }
            else if (missedLogHits[index] == 8) {
                // Try Database Log Hits
                ResolverStage[index] = 9;
                
                if (saveLastHeadshotFloat[index] != 0) {
                    
                    new_yaw = saveLastHeadshotFloat[index];
                    
                }
                else if (saveLastBaimFloat[index] != 0) {
                    
                    new_yaw = saveLastBaimFloat[index];
                    
                }
                else if (saveLastBaim30Float[index] != 0) {
                    
                    new_yaw = saveLastBaim30Float[index];
                    
                }
                else {
                    new_yaw = abs(entity->GetLowerBodyYawTarget() - angle);
                }
                
            }
            
            
            
            if (fakeshotMissedLast[index] <= 3) {
                
                if (abs(entity->GetLowerBodyYawTarget() - angle) > 35) {
                    // Enemy is using FakeAngle
                    new_yaw = angle - abs(entity->GetLowerBodyYawTarget() - angle);
                    ResolverStage[index] = 13;
                    fakeshotMissedLast[index] = missedLogHits[index];
                }
            }
            
            
        }
        else
        {
            if (is_nospread)
            {
                
                if (missedLogHits[index] <= 10) {
                    
                    switch (shots % 4)
                    {
                        case 1:
                            new_yaw = CurrentLowerbody - 15;
                            break;
                        case 2:
                            new_yaw = CurrentLowerbody + 40;
                            break;
                        case 3:
                            new_yaw = CurrentLowerbody + 15;
                            break;
                        case 4:
                            new_yaw = CurrentLowerbody - 40;
                            break;
                    }
                    
                }
                else {
                    
                    new_yaw = RandomFloat(-180, 180);
                    
                }
                
            }
            else
            {
                new_yaw = entity->GetLowerBodyYawTarget();
                ResolverStage[index] = 7;
                
            }
            
            if(IsMovingOnInAir)
            {
                angle = entity->GetLowerBodyYawTarget();
            }
            
        }
        
        
        new_yaw = (new_yaw);
        return new_yaw;
    }
    
    if(vars.aimbot.yresolve == 3)
    {
        //evolution
        static float oldlby = 0.0f;
        static bool bLowerBodyIsUpdated;
        float delta = angle - entity->GetLowerBodyYawTarget();
        if (entity->GetLowerBodyYawTarget() != oldlby) bLowerBodyIsUpdated = true;
        else bLowerBodyIsUpdated = false;
        
        if (bLowerBodyIsUpdated || fabsf(delta) >= 35.0f)
        {
            angle = entity->GetLowerBodyYawTarget();
            entity->oldlby = entity->GetLowerBodyYawTarget();
        }
        
        else
        {
            if (fabsf(delta) < 35.f && fabsf(delta) > 0.f)
                angle = entity->GetLowerBodyYawTarget() + delta;
        }
        return angle;
    }
    
    
    {
        static bool bLowerBodyIsUpdated;
        if (shotmissed > 3 && shotmissed < 21)
        {
            if (!bLowerBodyIsUpdated)
            {
                angle = entity->GetLowerBodyYawTarget();
            }
            else if (!bLowerBodyIsUpdated)
            {
                switch (shotmissed % 4)
                {
                    case 0: angle = entity->GetLowerBodyYawTarget(); break;
                    case 1: angle = entity->oldlby; break;
                    case 2: angle = entity->GetLowerBodyYawTarget() - 25; break;
                    case 3: angle = entity->oldlby + 25; break;
                }

            }
            else
                switch (shotmissed % 4)
            {
                case 0: angle = entity->oldlby; break;
                case 1: angle = entity->GetLowerBodyYawTarget() - 45; break;
                case 2: angle = entity->GetLowerBodyYawTarget() - 180; break;
                case 3: angle = entity->GetLowerBodyYawTarget() + 135; break;
            }

        }
        
        else if (shotmissed >= 2 && shotmissed <= 3)
            
        {
            if (bLowerBodyIsUpdated)
            {
                angle = entity->GetLowerBodyYawTarget();
            }
            else
                angle = entity->GetLowerBodyYawTarget();
        }
        else
        {
            if (bLowerBodyIsUpdated)
            {
                bool timer = false;
                if (timer){
                    angle = entity->GetLowerBodyYawTarget(); + rand() % 20;
                }else{
                    angle = entity->GetLowerBodyYawTarget(); - rand() % 100;
                }
            }
            else
                if (Lbywithin35)
                {
                    
                    if (HasFakeHead)
                    {
                        {
                            switch (shotmissed % 7)
                            {
                                case 0: angle = entity->oldlby + 15; break;
                                case 1: angle = entity->oldlby - 45; break;
                                case 2: angle = entity->oldlby + 65; break;
                                case 3: angle = angle - entity->GetLowerBodyYawTarget(); break;
                                case 4: angle = (angle + entity->GetLowerBodyYawTarget()) - 120; break;
                                case 5: angle = (angle + entity->GetLowerBodyYawTarget()) + 120; break;
                                case 6: angle = (angle - entity->GetLowerBodyYawTarget()) - (150 - rand() % 30); break;
                            }
                        }
                    }
                    else
                    {
                        {
                            switch (shotmissed % 7)
                            {
                                case 0: angle = entity->oldlby - 15; break;
                                case 1: angle = entity->oldlby + 15; break;
                                case 2: angle = entity->GetLowerBodyYawTarget() - 119; break;
                                case 3: angle = angle - 90; break;
                                case 4: angle = angle - 60; break;
                                case 5: angle = (angle + entity->GetLowerBodyYawTarget()) + 120; break;
                                case 6: angle = (angle - entity->GetLowerBodyYawTarget()) - (150 - rand() % 30); break;
                            }
                        }
                    }
                    
                }

        }
        if (maybeFakeWalking)
        {
            vector<int> hitboxes;
            
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            hitboxes.push_back(HITBOX_BELLY);
            hitboxes.push_back(HITBOX_PELVIS);
            hitboxes.push_back(HITBOX_UPPER_CHEST);
            
            angle = entity->oldlby - 30;
        }
        
        
        // Breaking LBY
        static float current_layer_activity = entity->GetAnimTime();
        static float previous_layer_activity = 0;
        
        if (current_layer_activity == 979){ // the current layer must be triggering 979
            {
                if (previous_layer_activity == 979) // the previous layer must be trigerring 979
                {
                    switch (shots % 3){
                        case 1: angle = entity->GetLowerBodyYawTarget() + 110;
                            break;
                        case 2: angle = entity->GetLowerBodyYawTarget() + 180;
                            break;
                        case 3: angle = entity->GetLowerBodyYawTarget() - 110;
                            break;
                    }
                    // we can tell now that he is surely breaking lby in some sort
                    angle = entity->GetLowerBodyYawTarget() - 180.f; // for the resolver it's enough here to just flip him, because we will backtrack him | unless u dont have backtrack
                }
            }
        }
    }
    
    if(vars.aimbot.yresolve == 4)
    {
        //evolution
        static float oldlby = 0.0f;
        static bool bLowerBodyIsUpdated;
        float delta = angle - entity->GetLowerBodyYawTarget();
        if (entity->GetLowerBodyYawTarget() != oldlby) bLowerBodyIsUpdated = true;
        else bLowerBodyIsUpdated = false;
        
        if (bLowerBodyIsUpdated || fabsf(delta) >= 35.0f)
        {
            angle = entity->GetLowerBodyYawTarget();
            entity->oldlby = entity->GetLowerBodyYawTarget();
        }
        
        else
        {
            if (fabsf(delta) < 35.f && fabsf(delta) > 0.f)
                angle = entity->GetLowerBodyYawTarget() + delta;
        }
        return angle;
                                  }
                                      
        
    {
        static bool bLowerBodyIsUpdated;
        if (shotmissed > 3 && shotmissed < 21)
        {
            if (!bLowerBodyIsUpdated)
            {
                angle = entity->GetLowerBodyYawTarget();
            }
            else if (!bLowerBodyIsUpdated)
            {
                switch (shots % 4)
                {
                    case 1: angle = - 30 + rand() % 45 - rand() % 51;
                        break;
                    case 2: angle = entity->GetLowerBodyYawTarget() + 20 - rand() % 35;
                        break;
                    case 3: angle = entity->GetLowerBodyYawTarget() + 45 % 30 - rand() % 90;
                        break;
                    case 4: angle = entity->GetLowerBodyYawTarget() - 90 - rand() % 90 - rand() % 40;
                        break;
                    case 5: angle = 160 - rand() % 90 - rand() % 40;
                        break;
                }
            }
            else
                angle = rand() % 180 - rand() % 45;
        }
        
        else if (shotmissed >= 2 && shotmissed <= 3)
            
        {
            if (bLowerBodyIsUpdated)
            {
                angle = entity->GetLowerBodyYawTarget();
            }
            else
                angle = entity->GetLowerBodyYawTarget();
        }
        else
        {
            if (bLowerBodyIsUpdated)
            {
                bool timer = false;
                if (timer){
                    angle = entity->GetLowerBodyYawTarget(); + rand() % 20;
                }else{
                    angle = entity->GetLowerBodyYawTarget(); - rand() % 100;
                }
            }
            else
            {
                bool timer = false;
                if (timer){
                    angle = entity->GetLowerBodyYawTarget(); + rand() % 20;
                }else
                    angle = entity->GetLowerBodyYawTarget(); - rand() % 20;
            }
        }
        if (maybeFakeWalking)
        {
            vector<int> hitboxes;
            
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            hitboxes.push_back(HITBOX_BELLY);
            hitboxes.push_back(HITBOX_PELVIS);
            hitboxes.push_back(HITBOX_UPPER_CHEST);
            
            angle = entity->oldlby - 30;
        }
        
        
        // Breaking LBY
        static float current_layer_activity = entity->GetAnimTime();
        static float previous_layer_activity = 0;
        
        if (current_layer_activity == 979){ // the current layer must be triggering 979
            {
                if (previous_layer_activity == 979) // the previous layer must be trigerring 979
                {
                    switch (shots % 3){
                        case 1: angle = entity->GetLowerBodyYawTarget() + 110;
                            break;
                        case 2: angle = entity->GetLowerBodyYawTarget() + 180;
                            break;
                        case 3: angle = entity->GetLowerBodyYawTarget() - 110;
                            break;
                    }
                    // we can tell now that he is surely breaking lby in some sort
                    angle = entity->GetLowerBodyYawTarget() - 180.f; // for the resolver it's enough here to just flip him, because we will backtrack him | unless u dont have backtrack
                }
            }
        }
    }
    if(vars.aimbot.yresolve == 5)
    {
        float last_moving_lby [ 65 ];
        
        bool Movingg;
        entity->GetVelocity( ).Length2D( ) > 1.f && ( entity->GetFlags() & FL_ONGROUND);
        
        bool Fakewalkk;
        Movingg && entity->GetVelocity().Length2D() < 45.f && !( entity->GetFlags( ) & FL_DUCKING );
        
        if ( Movingg ) {
            if ( Fakewalkk ) {
                angle = entity->GetLowerBodyYawTarget( ) - 180.f;
            }
            else
            {
                angle = entity->GetLowerBodyYawTarget( );
                last_moving_lby [ entity->GetIndex() ] = entity->GetLowerBodyYawTarget( );
            }
            if (HasFakeHead)
            {
                angle = angle - entity->GetLowerBodyYawTarget();
            }
        }
        else
        {
#define RandomFloat(min, max) (rand() % (max - min + 1) + min)
            angle += RandomFloat(35, 35);
            angle = last_moving_lby[ entity->GetIndex() ] + rand( ) % ( 25 - -25 + 1 ) + -25;
        }
        
    } // end of resolver 5
    
    if(vars.aimbot.yresolve == 6){
        angle += RandomFloat(35, 35);
    }
    
    if(vars.aimbot.yresolve == 7){
        angle = entity->GetLowerBodyYawTarget() + 180;
    }
    
}

void FixYaw(const CRecvProxyData *pData, void *pStruct, void *pOut) {
    float flYaw = pData->m_Value.m_Float;
    
    int index = ((C_BaseEntity*)pStruct)->GetIndex();
    
    gCorrections[index].y = flYaw;
    
    OldProxy_Y(pData, pStruct, pOut);
}
