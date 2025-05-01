//
// Created by Navo on 3/9/2023.
//

#ifndef VIAL_QC_CONSTANTS_H
#define VIAL_QC_CONSTANTS_H

namespace consts {
    namespace circul {
        namespace top {
            static int MODEL_CIRCLE_RADIUS = 280;
            static double MIN_SHAPE_SCORE = 0.5;
            static double MIN_SHAPE_SCALE = 0.3;
            static double MAX_SHAPE_SCALE = 3;
            static double MAX_SCORE_DEVIA = 0.05;
            static int MAX_COORD_DEVIA = 5;
        }
        namespace bottom {
            static int MODEL_CIRCLE_RADIUS = 220;
            static double MIN_SHAPE_SCORE = 0.5;
            static double MIN_SHAPE_SCALE = 0.3;
            static double MAX_SHAPE_SCALE = 3;
        }
    }
} // consts

#endif //VIAL_QC_CONSTANTS_H
