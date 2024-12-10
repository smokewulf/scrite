
from fastapi import FastAPI

app = FastAPI()

@app.get('/teamspace/studios/this_studio/scrite')
async def read_scrite():
    return {'message': 'Welcome to Scrite in this studio!'}

if __name__ == '__main__':
    import uvicorn
    uvicorn.run(app, host='0.0.0.0', port=8000)
