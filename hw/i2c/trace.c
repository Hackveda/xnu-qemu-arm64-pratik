/* This file is autogenerated by tracetool, do not edit. */

#include "qemu/osdep.h"
#include "trace.h"

uint16_t _TRACE_I2C_EVENT_DSTATE;
uint16_t _TRACE_I2C_SEND_DSTATE;
uint16_t _TRACE_I2C_RECV_DSTATE;
TraceEvent _TRACE_I2C_EVENT_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "i2c_event",
    .sstate = TRACE_I2C_EVENT_ENABLED,
    .dstate = &_TRACE_I2C_EVENT_DSTATE 
};
TraceEvent _TRACE_I2C_SEND_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "i2c_send",
    .sstate = TRACE_I2C_SEND_ENABLED,
    .dstate = &_TRACE_I2C_SEND_DSTATE 
};
TraceEvent _TRACE_I2C_RECV_EVENT = {
    .id = 0,
    .vcpu_id = TRACE_VCPU_EVENT_NONE,
    .name = "i2c_recv",
    .sstate = TRACE_I2C_RECV_ENABLED,
    .dstate = &_TRACE_I2C_RECV_DSTATE 
};
TraceEvent *hw_i2c_trace_events[] = {
    &_TRACE_I2C_EVENT_EVENT,
    &_TRACE_I2C_SEND_EVENT,
    &_TRACE_I2C_RECV_EVENT,
  NULL,
};

static void trace_hw_i2c_register_events(void)
{
    trace_event_register_group(hw_i2c_trace_events);
}
trace_init(trace_hw_i2c_register_events)
