import axios, { AxiosResponse } from 'axios';
import { ImageType } from '@/image';

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
  getImageList: (): Promise<ImageType[]> => requests.get('images', {}),
  getImage: (id: number): Promise<Blob> => requests.get(`images/${id}`, { responseType: "blob" }),
  createImage: (form: FormData): Promise<ImageType> => requests.post('images', form),
  deleteImage: (id: number): Promise<void> => requests.delete(`images/${id}`),
};


export async function getImageList() 
{
    try {
        return await api.getImageList();
    } catch (error) {
        console.error(error);
        return new Array<ImageType>();
    }
}

export async function getImageData(id:number)
{
    try {
        const response = await api.getImage(id);
        const reader = new window.FileReader();
        const promise = new Promise<string>(resolve => {
            reader.onload = () => resolve(reader.result as string);
        });
        reader.readAsDataURL(response);
        return await promise;
    } catch (e) {
        console.error(e)
        return "";
    }
}


