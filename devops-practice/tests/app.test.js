const request = require('supertest');
const { app, server } = require('../src/app');

describe('GET /', () => {
    it('should return Hello, World!', async () => {
        const res = await request(app).get('/');
        expect(res.statusCode).toEqual(200);
        expect(res.text).toBe('Hello, World!');
    });
    it('should return bad!', async () => {
        const res = await request(app).get('/9');
        expect(res.statusCode).toEqual(404);
        expect(res.text).toBe('Hello, World!');
    });

});

afterAll(done => {
    server.close(done);
});
