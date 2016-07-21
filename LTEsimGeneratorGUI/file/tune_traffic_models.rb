require 'traffic_model_tuner'

run('configuration.rb', args)

Logging.turnOnLogging()

# Test arguments
MOBILITY_MODEL = "WalkerStartAtEast"
CS_MODEL = "PowerOnOffPsCntRecover"
PS_MODEL = "LteBatStaticPing"

speed = TunableParameterData.new(MOBILITY_MODEL, "handovers", :get_successful_handovers, 30)
speed.base_value = 3
speed.tuning_value = speed.base_value * 3

granularity = TunableParameterData.new(MOBILITY_MODEL, "handovers", :get_successful_handovers, 30)
granularity.base_value = 0.7
granularity.tuning_value = granularity.base_value * 2
granularity.verify_equal_upto_value = 2

call_intensity = TunableParameterData.new(CS_MODEL, "attach", :get_number_of_attach)
call_intensity.base_value = 1.0
call_intensity.tuning_value = call_intensity.base_value * 0.5
call_intensity.use_less_than = true

call_duration = TunableParameterData.new(CS_MODEL, "attach", :get_number_of_attach)
call_duration.base_value = 1.0
call_duration.tuning_value = call_duration.base_value * 1.1
call_duration.use_less_than = true

ps_duration = TunableParameterData.new(PS_MODEL, "good tasks", :get_good_counter)
ps_duration.base_value = 1.0
ps_duration.tuning_value = ps_duration.base_value * 3
ps_duration.use_less_than = true

ps_intensity = TunableParameterData.new(PS_MODEL, "good tasks", :get_good_counter, 30)
ps_intensity.base_value = 1.0
ps_intensity.tuning_value = ps_intensity.base_value * 0.03
ps_intensity.use_less_than = true

tunable_parameters = { "speed" => speed,
                       "granularity" => granularity,
                       "call_intensity" =>call_intensity,
                       "call_duration" => call_duration,
                       "ps_duration" => ps_duration,
                       "ps_intensity" => ps_intensity
}

# Execute the tests
tuner = TrafficModelTuner.new(MOBILITY_MODEL, CS_MODEL, PS_MODEL, tunable_parameters)

tuner.setup
tuner.run_test_case("speed")
tuner.teardown

tuner.setup
tuner.tune_model("speed", true)
tuner.tune_model("call_intensity", true)
tuner.run_test_case("granularity")
tuner.teardown

tuner.setup
tuner.tune_model("call_duration", true, 0.1)
tuner.tune_model("ps_duration", true, 0.5)
tuner.tune_model("call_intensity", true, 10)
tuner.run_test_case("call_intensity")
tuner.teardown

tuner.setup
tuner.tune_model("ps_duration", true, 0.5)
tuner.tune_model("call_intensity", true, 10)
tuner.tune_model("call_duration", true, 0.1)
tuner.run_test_case("call_duration")
tuner.teardown

tuner.setup
tuner.run_test_case("ps_duration")
tuner.teardown

tuner.setup
tuner.tune_model("call_intensity", true)
tuner.tune_model("ps_duration", true, 0.5)
tuner.run_test_case("ps_intensity")
tuner.teardown


LteSimCli.show_result
Logging.restoreLogLevel
