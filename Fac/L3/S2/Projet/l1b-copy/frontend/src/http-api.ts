import axios, { AxiosResponse } from "axios";
import { Ref } from "vue";

export async function getImagesData(data: Ref<{ id: number; name: string }[]>) {
    try {
        const res = await axios.get('/images');
        data.value = res.data;
    }
    catch (error) {
        console.log(error);
    }
}

const instance = axios.create({
    baseURL: "/",
    timeout: 15000,
});

const responseBody = (response: AxiosResponse) => response.data;

const requests = {
    get: (url: string, param: {}) => instance.get(url, param).then(responseBody),
    post: (url: string, body: {}) => instance.post(url, body, { headers: { "Content-Type": "multipart/form-data" }, }).then(responseBody),
    put: (url: string, body: {}) => instance.put(url, body).then(responseBody),
    delete: (url: string) => instance.delete(url).then(responseBody)
};

export const api = {
    getImageList: (): Promise<{ id: number; name: string }[]> => requests.get('images', {}),
    getImage: (id: number): Promise<Blob> => requests.get(`images/${id}`, { responseType: "blob" }),
    createImage: (form: FormData): Promise<{ id: number; name: string }> => requests.post('images', form),
    deleteImage: (id: number): Promise<void> => requests.delete(`images/${id}`),
};