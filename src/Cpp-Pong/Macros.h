#pragma once

#define SAFE_DELETE(p) { if(p) { delete(p); }}
#define SAFE_RELEASE(p) { if (p) { p->Release(); }}