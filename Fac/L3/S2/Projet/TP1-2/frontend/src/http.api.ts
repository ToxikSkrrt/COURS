import axios from "axios";
import { Ref } from "vue";

export async function getImagesData(data: Ref<{ name: string; id: number }[]>) {
    try {
        const res = await axios.get('/images');
        data.value = res.data;
    }
    catch (error) {
        console.log(error);
    }
}