﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NEATc__Interpreter;

namespace NeuralUtil
{
    public static class Formatting
    {
        public static double Normalise(this double value, double min, double max)
        {
            double mn = Math.Min(min, max);
            double mx = Math.Max(min, max);
            double range = mx - mn;
            double outcome = (value - mn) / range;
            //Output.GenerateOutput("Mn: {0}; Mx: {1}; Range: {2}; Outcome: {3};", mn, mx, range, outcome);
            return outcome;
        }
        public static double ReverseNormalise(this double value, double min, double max)
        {
            double mn = Math.Min(min, max);
            
            double mx = Math.Max(min, max);
            double range = mx - mn;
            double outcome = value * range + mn;
            //Output.GenerateOutput("Value: {0}; Mn: {1}; Mx: {2}; Range: {3}; Outcome: {4};",value, mn, mx, range, outcome);
            return outcome;
        }
        public static float RoundToFloat(this double value)
        {
            return (float)Math.Round(value, 4);
        }
    }
}